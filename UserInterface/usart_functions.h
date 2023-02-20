#include "stm32f0xx.h"

// convert hex to decimal
uint8_t hexToDec(uint8_t hexNumber);
// Send single character to UART
void sendChar(USART_TypeDef* USARTx, uint8_t ch);
void sendUsartMessage(data_packet_t* data_packet);