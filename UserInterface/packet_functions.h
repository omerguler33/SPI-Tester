
#ifndef PACKET_FUNCTIONS_H
#define PACKET_FUNCTIONS_H

/******************************* #includes ************************************/
#include "stm32f0xx.h"

/******************************* #prototypes **********************************/
void INT8_break         (uint8_t* packet, uint16_t* index, const int8_t* data);
void UINT8_break        (uint8_t* packet, uint16_t* index, const uint8_t* data);
void INT16_break        (uint8_t* packet, uint16_t* index, const int16_t* data);
void UINT16_break       (uint8_t* packet, uint16_t* index, const uint16_t* data);
void INT32_break        (uint8_t* packet, uint16_t* index, const int32_t* data);
void UINT32_break       (uint8_t* packet, uint16_t* index, const uint32_t* data);

void INT8_merge         (const uint8_t* packet, uint16_t* index, int8_t* data);
void UINT8_merge        (const uint8_t* packet, uint16_t* index, uint8_t* data);
void INT16_merge        (const uint8_t* packet, uint16_t* index, int16_t* data);
void UINT16_merge       (const uint8_t* packet, uint16_t* index, uint16_t* data);
void INT32_merge        (const uint8_t* packet, uint16_t* index, int32_t* data);
void UINT32_merge       (const uint8_t* packet, uint16_t* index, uint32_t* data);

#endif /* PACKET_FUNCTIONS_H */