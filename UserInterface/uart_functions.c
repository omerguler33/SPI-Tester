/**
  ******************************************************************************
  * @file    Project/wheelchair_CU/uart_functions.c 
  * @author  Ozgur BOSTAN, Huseyin AYDOGMUS
  * @version V1.0
  * @date    08-December-2016
  * @brief   Main uart functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 RFtek Electronics</center></h2>
  *
  * Licensed under RFtek Electronics SW License Agreement, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.rftek.com.tr
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "data_transfer.h"
#include "main.h"

// convert hex to decimal
uint8_t hexToDec(uint8_t hexNumber)
{
  uint8_t firstDigit, secondDigit;
  uint8_t decimalNumber;
  
  firstDigit = hexNumber >> 4;
  secondDigit = hexNumber & 0x0F;
  
  decimalNumber = firstDigit * 16 + secondDigit;
  
  return decimalNumber;
}

// Send single character to UART
void sendChar(USART_TypeDef* USARTx, uint8_t ch) 
{
  USARTx->TDR = ch; 
  while (!(USARTx->ISR& USART_ISR_TC)); // wait for "Transmission Complete" flag 
}

void sendUsartMessage(data_packet_t* data_packet)
{
  sendChar(USART1, hexToDec(data_packet->sync_byte1));
  sendChar(USART1, hexToDec(data_packet->sync_byte2));
  sendChar(USART1, hexToDec(data_packet->packet_type));
  sendChar(USART1, hexToDec(data_packet->data_size));
  
  if(data_packet->data_size > 0)
  {
    for(uint8_t i = 0; i < data_packet->data_size; i++)
    {
      sendChar(USART1, hexToDec(data_packet->data[i]));
    }
  }
  
  sendChar(USART1, hexToDec(data_packet->crc_high));
  sendChar(USART1, hexToDec(data_packet->crc_low));
}