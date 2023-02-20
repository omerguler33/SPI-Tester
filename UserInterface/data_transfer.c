
#include "data_transfer.h"
#include "packet_functions.h"
#include "crc.h"
#include "usart_functions.h"

#define CRC_BUFFER_SIZE         33
extern uint8_t CRCBuffer[CRC_BUFFER_SIZE];
reg_32               regData;
reg_32               USARTSend ;


captured_packet_t empty_packet = {0};
extern uint8_t button ;
extern uint8_t ConfigAddress1 ,ConfigAddress2, ConfigAddress3,ConfigAddress4 ;
extern uint8_t adres1 , adres2 , adres3 , adres4 ;
extern uint8_t ConfigAddress ;
extern uint8_t ConfigData ;
extern uint8_t SPISendData , SPISendData1, SPISendData2 ,SPISendData3 , SPISendData4 ;
extern uint8_t deviceSlctn ;
extern uint8_t address ;
void capture_data(captured_packet_t* captured_packet, const uint8_t* captured_data, const uint32_t captured_data_size)
{
  uint32_t i = 0;
  
  for(i = 0; i < captured_data_size; i++)
  {
    //captured_packet->incoming_byte_number++;
    
    switch(captured_packet->data_capture_status)
    {
      case CAPTURE_SYNC1:
      {
        if(SYNC_BYTE1 == captured_data[i])
        {
          captured_packet->data_packet.sync_byte1       = captured_data[i];
          captured_packet->data_capture_status          = CAPTURE_SYNC2;
        }
        
        break;
      }
      
      case CAPTURE_SYNC2:
      {
        if(SYNC_BYTE2 == captured_data[i])
        {
          captured_packet->data_packet.sync_byte2       = captured_data[i];
          captured_packet->data_capture_status          = CAPTURE_PACKET_TYPE;
        }
        else
        {
          captured_packet->data_capture_status          = CAPTURE_SYNC1;
          captured_packet->data_counter                 = 0;
        }
        
        break;
      }
	  
      case CAPTURE_PACKET_TYPE:
      {
        captured_packet->data_packet.packet_type        = captured_data[i];
        captured_packet->data_capture_status            = CAPTURE_DATA_SIZE;
        
        break;
      }
            
      case CAPTURE_DATA_SIZE:
      {
        captured_packet->data_packet.data_size          = captured_data[i];              
        
        if(captured_packet->data_packet.data_size == 0)
        {
          captured_packet->data_capture_status          = CAPTURE_CRC1;
        }
        else
        {
          captured_packet->data_capture_status          = CAPTURE_DATA;
        }
        
        break;
      }
      
      case CAPTURE_DATA:
      {
        captured_packet->data_packet.data[captured_packet->data_counter] = captured_data[i];
        captured_packet->data_counter++;
        
        if(captured_packet->data_counter >= captured_packet->data_packet.data_size)
        {
          captured_packet->data_capture_status          = CAPTURE_CRC1;
        }
        
        break;
      }    
           
      case CAPTURE_CRC1:
      {
        captured_packet->data_packet.crc_high           = captured_data[i];
        captured_packet->data_capture_status            = CAPTURE_CRC2;
        
        break;
      }
      
      case CAPTURE_CRC2:
      {
        uint8_t data_packet_size                        = 0;
        uint16_t crc_calculated                         = 0;
        uint16_t crc_captured                           = 0;
        
        captured_packet->data_packet.crc_low            = captured_data[i];
        data_packet_size                                = captured_packet->data_packet.data_size;
        
        CRCBufferUpdate(&(captured_packet->data_packet));
        crc_calculated                                  = crcCalc_wTable((uint8_t *)CRCBuffer,
                                                                         data_packet_size + 
                                                                         PACKET_SIZE_EXCEPT_DATA);
        crc_captured                                    = (captured_packet->data_packet.crc_high << 8) +
                                                           captured_packet->data_packet.crc_low;
        
        if(crc_calculated == crc_captured)
        {
          //captured_packet->faultless_packet_number++;
          resolve_packet(&(captured_packet->data_packet));
        }
        else
        {
          captured_packet->faulty_packet_number++;
        }
        
        captured_packet->data_capture_status            = CAPTURE_SYNC1;
        captured_packet->data_counter                   = 0;
        
        break;
      }
      
      default:
      {
        captured_packet->data_capture_status            = CAPTURE_SYNC1;
        captured_packet->data_counter                   = 0;
      }
    }
  }
}

void resolve_packet(const data_packet_t* captured_packet)
{
  uint16_t tempValue = 0 ;
  data_packet_t packet = {0};
  
  switch(captured_packet->packet_type)
  { 
    case REGISTER_1:      
    {
      resolve_cu_data_packet(captured_packet, &regData);
      //here send the data to related register "&data->regValue"  is the value to be send
      tempValue = SPI1->CR1 ;
      tempValue |= ((regData.regValue & 0xFFFF) == SPI_BaudRatePrescaler_32 ) ? SPI_BaudRatePrescaler_32 : (regData.regValue & 0xFFFF) ;
      SPI1->CR1 = tempValue ;
      
      break;
    }
    case REGISTER_2:
    {
         resolve_cu_data_packet(captured_packet, &regData);
         tempValue = SPI1->CR1 ;
         tempValue |= ((regData.regValue & 0xFFFF ) == SPI_CPHA_1Edge ) ? SPI_CPHA_1Edge : (regData.regValue & 0xFFFF ) ;
         SPI1->CR1 = tempValue ;
      
      break;
    }
    case REGISTER_3:
    {    
         
         resolve_cu_data_packet(captured_packet, &regData);
         tempValue = SPI1->CR1 ;
         tempValue |= ((regData.regValue & 0xFFFF) == SPI_CPOL_Low) ? SPI_CPOL_Low : (regData.regValue & 0xFFFF ) ;
         SPI1->CR1 = tempValue ;
        
      break;
    }
    case REGISTER_4:
    {
        resolve_cu_data_packet(captured_packet, &regData);
        tempValue = SPI1->CR2 ;
        tempValue |= ((regData.regValue & 0xFFFF) == SPI_DataSize_8b) ? SPI_DataSize_8b : (regData.regValue & 0xFFFF ) ;
        SPI1->CR2 = tempValue ; 
        
      break;
    }
    case REGISTER_5:
    {
       resolve_cu_data_packet(captured_packet, &regData);
       button  = (uint8_t)(regData.regValue & 0xFF) ;   
      //tempValue = SPI1->CR1 ;
      // tempValue |= ((regData.regValue & 0xFFFF) == SPI_Direction_2Lines_FullDuplex) ? SPI_Direction_2Lines_FullDuplex : (regData.regValue & 0xFFFF );
      //SPI1->CR1 = tempValue ;
        
      break;
    }
    case REGISTER_6:
    {
       resolve_cu_data_packet(captured_packet, &regData);
       tempValue = SPI1->CR1 ;
       tempValue |= ((regData.regValue & 0xFFFF)== SPI_FirstBit_MSB ) ? SPI_FirstBit_MSB : (regData.regValue & 0xFFFF );
       SPI1->CR1 = tempValue ;
        
      break;
    }
    case REGISTER_7:
    {
        resolve_cu_data_packet(captured_packet, &regData);
        ConfigAddress = (uint8_t)(regData.regValue & 0xFF) ;
        
        switch(deviceSlctn)
        {
        
        case 1 :
          ConfigAddress1 = ConfigAddress ;
          break;
        case 2 : 
          ConfigAddress2 = ConfigAddress ;
          break ;
        case 3 : 
          ConfigAddress3 = ConfigAddress ;
        break ;
        case 4 : 
          ConfigAddress4 = ConfigAddress ;
          break ;
        default :
          break ;
    
        }
        
        
       //tempValue = SPI1->CR1 ;
       //tempValue |= ((regData.regValue & 0xFFFF) == SPI_Mode_Master ) ? regData.regValue : (regData.regValue & 0xFFFF ) ;
       // SPI1->CR1 = tempValue ;
      break;
    }
    case REGISTER_8:
    {
        resolve_cu_data_packet(captured_packet, &regData);
        address = (uint8_t)(regData.regValue & 0xFF) ;
        
        switch(deviceSlctn)
        {
        
        case 1 :
          adres1 = address ;
          break;
        case 2 : 
          adres2 = address ;
          break ;
        case 3 : 
          adres3 = address ;
        break ;
        case 4 : 
          adres4 = address ;
          break ;
        default :
          break ;
        
        
        }
        
        //tempValue = SPI1->CR1 ;
        //empValue |= ((regData.regValue & 0xFFFF) == SPI_NSS_Soft ) ? SPI_NSS_Soft : (regData.regValue & 0xFFFF ) ; 
        //SPI1->CR1 = tempValue ;
        
      break;
    }
    case REGISTER_9:
    {
      // the value that i send to sensor
      
     uint16_t tempValue = 0 ;
     
        resolve_cu_data_packet(captured_packet, &regData);
        tempValue = SPI1->CR2 ;
        
        if((( tempValue >> 8) & (0x0F)) == 15 )
        {
         
          SPISendData = (uint16_t)(regData.regValue & 0xFFFF) ;
        
        }
        else
        {
          
          SPISendData = (uint8_t)(regData.regValue & 0xFF) ;
        
        }
        
        switch(deviceSlctn)
        {
        
        case 1 :
          SPISendData1 = SPISendData ;
          break;
        case 2 : 
          SPISendData2 = SPISendData ;
          break ;
        case 3 : 
          SPISendData3 = SPISendData ;
        break ;
        case 4 : 
          SPISendData4 = SPISendData ;
          break ;
        default :
          break ;        
        
        }
        
      break;
    }
    case REGISTER_10:
    {
        resolve_cu_data_packet(captured_packet, &regData);
        deviceSlctn = (regData.regValue & 0xFF) ; 
        
      break;
    }
         
    default:
    
      break;
    
    }
  }


void resolve_cu_data_packet(const data_packet_t *data_packet, reg_32 *regData)
{
  uint16_t data_size_index = 0;
  UINT32_merge(data_packet->data, &data_size_index, &regData->regValue);
  //USARTSend.regValue = (uint32_t)SPISendData ;
  // sendDataToInterface(REGISTER_1,&(USARTSend.regValue));
  
  //written for testing
  //use function as this format to send data from uart to serialport
  // const uint32_t* test = &regData->regValue;
  //for(int i =0; i<5;i++) {
  //sendDataToInterface(REGISTER_1,&regData->regValue);
  // for(int i=0; i<10000000;i++){}
  // } 
}

void sendDataToInterface(uint8_t packet_type, const uint32_t* regValue){
  data_packet_t packet = {0}; 
  uint16_t data_size_index = 0;    
  
  packet.packet_type = packet_type;
  packet.data_size = 4;// 4 data (per 1 byte) for 32bit data
  
  UINT32_break(packet.data, &data_size_index, regValue);
  pack_data(&packet) ;
  sendUsartMessage(&packet) ;           
}

void pack_data(data_packet_t* data_packet)//data yok
{
  uint16_t crc_calculated       = 0;
  
  data_packet->sync_byte1       = SYNC_BYTE1;
  data_packet->sync_byte2       = SYNC_BYTE2;
  CRCBufferUpdate(data_packet);
  crc_calculated                = crcCalc_wTable((uint8_t *)CRCBuffer,
                                                 data_packet->data_size +
                                                 PACKET_SIZE_EXCEPT_DATA);
  
  data_packet->crc_high         = (uint8_t)((crc_calculated & 0xFF00) >> 8);
  data_packet->crc_low          = (uint8_t)(crc_calculated & 0x00FF);
}
