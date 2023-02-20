#include "data_transfer.h"
#include "crc.h"
#include "main.h"
#include "usart_functions.h" 
#include <string.h> 

#define  SPI_DR_Addr   (uint32_t)0x4001300C  // USED FOR SPI DMA CONFIGURATION 

GPIO_InitTypeDef GPIO_InitStructure ;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
SPI_InitTypeDef SPI_InitStructure ;
DMA_InitTypeDef DMA_InitStructure ; 

extern reg_32 regData ;
extern reg_32 USARTSend ;
uint8_t button ;
uint8_t address = 0;
uint8_t deviceSlctn ;
uint8_t SPIReceiveData1 = 0 , SPIReceiveData2 = 0 ,SPIReceiveData3 = 0 , SPIReceiveData4 = 0  ; 
uint8_t SPISendData ,SPISendData1,SPISendData2,SPISendData3, SPISendData4 ;
uint8_t ConfigAddress ;
uint8_t s1 = 0 ,s2 = 0 ,s3 = 0 ,s4 = 0 ; 
uint8_t adres1 , adres2 , adres3, adres4 ;
uint8_t ConfigAddress1 ,ConfigAddress2, ConfigAddress3,ConfigAddress4 ;



static void SPI_TX_MultiByte(uint8_t adres , uint16_t pData) ;
static uint16_t SPI_RX_MultiByt(uint8_t adres) ;
static uint8_t SPI_Rx(uint8_t adres) ;
static void SPI_Tx(uint8_t adres , uint8_t pData );
uint8_t SPI_ReceiveData(uint8_t pData) ;
static void GPIO_NSS_Config(void) ;
static void SPI_Config(void) ;
static void USART_Config(void);
static void DMA_Config(void) ;

uint8_t dataLength = 0;
uint8_t dataSize = 0;
uint8_t uartDataReady = 0;
uint8_t itReceivedValues[100] = {0};
captured_packet_t captured_packet = {0};


int main()
{
  
  GPIO_NSS_Config() ;
  
  SPI_Config() ;
  DMA_Config() ;  
  crcInitForTable();
  USART_Config();
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

   while(1)
  {
    
    //strcat(array, "1" ) ;
    //sendToUsart(USART1, array , sizeof(array)) ;
    //for(int i = 0 ; i<1000000 ; i++) ;
    
          
   if(button)
   {

    switch (deviceSlctn)
    {
      
    case 1 : 
       
          if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
           
           GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
           uint16_t SPIReceiveData1 = SPI_RX_MultiByt(adres1);  
           GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ; 
           uint16_t s1=  SPIReceiveData1 ;
           USARTSend.regValue = (uint32_t)s1 ; 
           
           sendDataToInterface(REGISTER_1,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;  
         
          
          }
          else
          {
            
           GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
           SPIReceiveData1 = SPI_Rx(adres1);  
           GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ;
           s1= SPIReceiveData1 ;
           USARTSend.regValue = (uint32_t)s1 ; 
           sendDataToInterface(REGISTER_1,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;         
         
          }
          
       break;
         
    case 2 :
            if((( SPI1->CR2 >> 8) & (0x0F)) == 15)
          {
            
           GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
           uint16_t SPIReceiveData2 = SPI_RX_MultiByt(adres2);  
           GPIO_SetBits(GPIOB, GPIO_Pin_1 ) ; 
           uint16_t s2 = SPIReceiveData2 ;  
           USARTSend.regValue = (uint32_t)s2 ; 
           sendDataToInterface(REGISTER_2,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;           
          }
          else
          {
       
           GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ; 
           SPIReceiveData2 = SPI_Rx(adres2); 
           GPIO_SetBits(GPIOB, GPIO_Pin_1 ) ;
           s2 = SPIReceiveData2 ;
           USARTSend.regValue = (uint32_t)s2 ; 
           sendDataToInterface(REGISTER_2,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;            
          }
          
         break;
         
    case 3 :
      
             if((( SPI1->CR2 >> 8) & (0x0F)) == 15)
          {
         
           GPIO_ResetBits(GPIOB, GPIO_Pin_2 ) ;
           uint16_t SPIReceiveData3 = SPI_RX_MultiByt(adres3);  
           GPIO_SetBits(GPIOB, GPIO_Pin_2 ) ; 
           uint16_t s3 = SPIReceiveData3 ;
           USARTSend.regValue = (uint32_t)s3 ; 
           sendDataToInterface(REGISTER_3,&(USARTSend.regValue ));
           for(int i = 0  ; i < 10000 ; i ++ ) ;            
          }
          else
          {
         
           GPIO_ResetBits(GPIOB, GPIO_Pin_2 ) ;
           SPIReceiveData3 = SPI_Rx(adres3);  
           GPIO_SetBits(GPIOB, GPIO_Pin_2 ) ; 
           s3 = SPIReceiveData3 ;
           USARTSend.regValue = (uint32_t)s3 ; 
           sendDataToInterface(REGISTER_3,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;            
          }
          
          break;
          
    case 4 :
          
            if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )
          {
            
           GPIO_ResetBits(GPIOB, GPIO_Pin_11 ) ;
           uint16_t SPIReceiveData4 = SPI_RX_MultiByt(adres4);  
           GPIO_SetBits(GPIOB, GPIO_Pin_11 ) ; 
           uint16_t s4 = SPIReceiveData4 ;
           USARTSend.regValue = (uint32_t)s4 ; 
           sendDataToInterface(REGISTER_4,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;           
          }
          else
          {
            
           GPIO_ResetBits(GPIOB, GPIO_Pin_11) ;
           SPIReceiveData4 = SPI_Rx( adres4 ) ;  
           GPIO_SetBits( GPIOB, GPIO_Pin_11 ) ; 
           s4 = SPIReceiveData4 ;
           USARTSend.regValue = (uint32_t)s4 ; 
           sendDataToInterface(REGISTER_4,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;            
          }
      break ;
      
    case 5 :
        
      
 
           if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
           
           GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
           uint16_t SPIReceiveData1 = SPI_RX_MultiByt(adres1);  
           GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ; 
           uint16_t s1=  SPIReceiveData1 ;
           USARTSend.regValue = (uint32_t)s1 ; 
           sendDataToInterface(REGISTER_2,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;  
           
           GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
           SPIReceiveData2 = SPI_RX_MultiByt(adres2);  
           GPIO_SetBits(GPIOB, GPIO_Pin_1 ) ; 
           uint16_t s2=  SPIReceiveData2 ;
           USARTSend.regValue = (uint32_t)s2 ; 
           sendDataToInterface(REGISTER_1,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;  
          
          
          }
          else
          {
            
           GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
           SPIReceiveData1 = SPI_Rx(adres1);  
           GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ;
           s1= SPIReceiveData1 ;
           USARTSend.regValue = (uint32_t)s1 ; 
           sendDataToInterface(REGISTER_2,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ; 
           
           
           GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
           SPIReceiveData2 = SPI_Rx(adres2);  
           GPIO_SetBits(GPIOB, GPIO_Pin_1 ) ;
           s2= SPIReceiveData2 ;
           USARTSend.regValue = (uint32_t)s2 ; 
           sendDataToInterface(REGISTER_1,&(USARTSend.regValue ));
           for(int i = 0  ; i < 1000000 ; i ++ ) ;   
          
           
          }
          
     break ;     
      
    default :
      break ;
    
    }
    }
  }
}

//*************************************************************************************

void USART1_IRQHandler(void)
{
  uint16_t receivedData ;
  while(!USART_GetITStatus(USART1, USART_IT_RXNE)){}
  USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  receivedData = USART_ReceiveData(USART1);
  itReceivedValues[dataLength] = receivedData & 0x00FF;
  dataLength++;
  
    
  if(itReceivedValues[0] == SYNC_BYTE1 && itReceivedValues[1] == SYNC_BYTE2 && dataLength == 4)
  {
    dataSize = itReceivedValues[3];
  }
  if(dataLength == dataSize + PACKET_SIZE_WITH_CRC)//PACKET_SIZE_WITH_CRC = 6
  {
    uartDataReady = 1;
    dataSize = 0;
  }
  
  if(uartDataReady == 1)
  {
    capture_data(&captured_packet,itReceivedValues, dataLength);
    dataLength = 0;
    uartDataReady=0;
  }
  
   switch (deviceSlctn)
    {
      
    case 1 : 
      
         if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
            SPI_TX_MultiByte(ConfigAddress1, SPISendData1) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_0) ;   
          }
          else
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_0 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
            SPI_Tx(ConfigAddress1, SPISendData1) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_0) ;
            
          }     
          
       break;
         
    case 2 :
         if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_1 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
            SPI_TX_MultiByte(ConfigAddress2, SPISendData2) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_1) ;   
          }
          else
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_1) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
            SPI_Tx(ConfigAddress2, SPISendData2) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_1) ;
            
          }     
          
         break;
         
    case 3 :
      
         if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_2 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_2 ) ;
            SPI_TX_MultiByte(ConfigAddress3, SPISendData3) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_2) ;   
          }
          else
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_2 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_2 ) ;
            SPI_Tx(ConfigAddress3, SPISendData3) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_2) ;
            
          }     
          
          break;
          
    case 4 :
          
         if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_11 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_11 ) ;
            SPI_TX_MultiByte(ConfigAddress4, SPISendData4) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_11) ;   
          }
          else
          {
             
            GPIO_SetBits(GPIOB, GPIO_Pin_11 ) ;
            GPIO_ResetBits(GPIOB, GPIO_Pin_11 ) ;
            SPI_Tx(ConfigAddress4, SPISendData4) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_11) ;
            
          }     
      break ;
    case 5 :
      
         if((( SPI1->CR2 >> 8) & (0x0F)) == 15 )               // SPI_InitStructure.SPI_DataSize == SPI_DataSize_16b
          {
             
            GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
            SPI_TX_MultiByte(ConfigAddress1, SPISendData1) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_0) ;  
            
            
            GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
            SPI_TX_MultiByte(ConfigAddress2, SPISendData2) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_1) ;            
          }
          else
          {
             
            
            GPIO_ResetBits(GPIOB, GPIO_Pin_0 ) ;
            SPI_Tx(ConfigAddress1, SPISendData1) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_0) ;
            
           
            GPIO_ResetBits(GPIOB, GPIO_Pin_1 ) ;
            SPI_Tx(ConfigAddress2, SPISendData2) ;   // 0x1b   0x8 
            GPIO_SetBits(GPIOB, GPIO_Pin_1) ;            
            
          }        
      
      
      break;
    default :
      break ;

    }  
  
}

//*****************************************************************************
static void SPI_Tx(uint8_t adres , uint8_t pData )
{
  
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , adres) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
    
  // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_ReceiveData8(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;
     
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , pData) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
    
    
   // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_ReceiveData8(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;

}
//*****************************************************************************

static void SPI_TX_MultiByte(uint8_t adres , uint16_t pData) 
{

  while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , adres) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
    
  //  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_ReceiveData8(SPI1) ;
    
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;
     
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    
    SPI_I2S_SendData16(SPI1 , pData) ;
    
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
  
   // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_ReceiveData8(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;

}

//*****************************************************************************

static uint8_t SPI_Rx(uint8_t adres) 
{
    uint8_t ReceivedValue = 0 ;
    
    adres = adres |  0x80 ;
    
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , adres) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )) ;
    
    //while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    ReceivedValue = SPI_ReceiveData8(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;
    
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , 0x00) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
    
   // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_ReceiveData8(SPI1)  ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;

 return ReceivedValue ; 
}

//*****************************************************************************

static uint16_t SPI_RX_MultiByt(uint8_t adres) 
{

   uint16_t ReceivedValue = 0 ;
    
    adres = adres |  0x80 ;
    
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_SendData8(SPI1 , adres) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )) ;
    
    //while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    ReceivedValue = SPI_I2S_ReceiveData16(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;
    
    while(SPI_I2S_GetFlagStatus( SPI1 , SPI_I2S_FLAG_TXE) == RESET ) ;
    SPI_I2S_SendData16(SPI1 , 0x0000) ;
    while( SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_BSY )  ) ;
    
   // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET) ;
    SPI_I2S_ReceiveData16(SPI1) ;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)) ;

 return ReceivedValue ; 

}


//*****************************************************************************

void USART_Config(void)
{
  //uart pin config
  
  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);//tx pa9
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);//rx pa10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
 
  //uart config
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  //nvic config and init
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  
  //uart init
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1,ENABLE);
}

//****************************************************************************
static void SPI_Config(void)
{
 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE) ; 
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI1EN , ENABLE ) ; 
  
    
  GPIO_PinAFConfig(GPIOA , GPIO_PinSource5 , GPIO_AF_0 ) ;
  GPIO_PinAFConfig(GPIOA , GPIO_PinSource6 , GPIO_AF_0 ) ;
  GPIO_PinAFConfig(GPIOA , GPIO_PinSource7 , GPIO_AF_0 ) ;
  // GPIO_PinAFConfig(GPIOA , GPIO_PinSource7 , GPIO_AF_0 ) ; 
  
  // SPI AF configuration 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF ;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
  
  GPIO_Init(GPIOA , &GPIO_InitStructure ) ;
 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32 ;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge ;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High ;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b ;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master ; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft ; 
  
  SPI_Init(SPI1 , &SPI_InitStructure ) ;
  SPI_Cmd(SPI1, ENABLE) ;
 
}

//***********************************************************************
static void GPIO_NSS_Config(void)
{

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB ,ENABLE ) ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;  
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_Level_3 ;
  GPIO_Init(GPIOB , &GPIO_InitStructure ) ;

}

//**********************************************************************

static void DMA_Config(void) 
{
  RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN , ENABLE ) ;
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFGEN, ENABLE);
  
  // COMMON DMA CONFIGURATION 
  DMA_InitStructure.DMA_BufferSize = sizeof(uint8_t) ;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ; 
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable ;
  
  // DMA1 CHANNEL3  CONFIGURATION SPI Tx
  
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(SPISendData );
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST ;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_Addr ;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);
  
  DMA_RemapConfig(DMA1, DMA1_CH3_SPI1_TX);

  // DMA1 CHANNEL2 CONFIGURATION SPI Rx 
  
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(SPIReceiveData1) ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_Addr ;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);
   
  /* DMA remap Channel2 to SPI1 Rx */
  DMA_RemapConfig(DMA1, DMA1_CH2_SPI1_RX);
  
  SPI_I2S_DMACmd(SPI1 , SPI_I2S_DMAReq_Tx , ENABLE ) ;
  SPI_I2S_DMACmd(SPI1 , SPI_I2S_DMAReq_Rx , ENABLE) ;
  DMA_Cmd(DMA1_Channel3, ENABLE )  ;
  DMA_Cmd(DMA1_Channel2 , ENABLE ) ;
  
  //SPI_Cmd(SPI1, ENABLE) ;
 // while(!DMA_GetFlagStatus(DMA1_FLAG_TC2)); 
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC3)); 
 
  /* Clear DMA1 TC flags */
  
  DMA_ClearFlag(DMA1_FLAG_TC2);
  DMA_ClearFlag(DMA1_FLAG_TC3);
 
  
  /* Disable DMA1 channels */
  DMA_Cmd(DMA1_Channel3, DISABLE )  ;
  DMA_Cmd(DMA1_Channel2 , DISABLE ) ;
  
}

