#include "packet_functions.h"
////////////////////////////////////////////////////////////////////////////////
void INT8_break (uint8_t* packet, uint16_t* index, const int8_t* data)
{
  packet[(*index) + 0]  = ((uint8_t*) data)[0];
  *index                = *index + sizeof(int8_t);
}

void INT8_merge (const uint8_t* packet, uint16_t* index, int8_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 0];
  *index                = *index + sizeof(int8_t);
}
////////////////////////////////////////////////////////////////////////////////
void UINT8_break (uint8_t* packet, uint16_t* index, const uint8_t* data)
{
  packet[(*index) + 0]  = ((uint8_t*) data)[0];
  *index                = *index + sizeof(uint8_t);
}

void UINT8_merge (const uint8_t* packet, uint16_t* index, uint8_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 0];
  *index                = *index + sizeof(uint8_t);
}
////////////////////////////////////////////////////////////////////////////////
void INT16_break (uint8_t* packet, uint16_t* index, const int16_t* data)
{
  packet[(*index) + 1]  = ((uint8_t*) data)[0];
  packet[(*index) + 0]  = ((uint8_t*) data)[1];
  *index                = *index + sizeof(int16_t);
}

void INT16_merge (const uint8_t* packet, uint16_t* index, int16_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 1];
  ((uint8_t*) data)[1]  = packet[(*index) + 0];
  *index                = *index + sizeof(int16_t);
}
////////////////////////////////////////////////////////////////////////////////
void UINT16_break (uint8_t* packet, uint16_t* index, const uint16_t* data)
{
  packet[(*index) + 1]  = ((uint8_t*) data)[0];
  packet[(*index) + 0]  = ((uint8_t*) data)[1];
  *index                = *index + sizeof(uint16_t);
}

void UINT16_merge (const uint8_t* packet, uint16_t* index, uint16_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 1];
  ((uint8_t*) data)[1]  = packet[(*index) + 0];
  *index                = *index + sizeof(uint16_t);
}
////////////////////////////////////////////////////////////////////////////////
void INT32_break (uint8_t* packet, uint16_t* index, const int32_t* data)
{
  packet[(*index) + 3]  = ((uint8_t*) data)[0];
  packet[(*index) + 2]  = ((uint8_t*) data)[1];
  packet[(*index) + 1]  = ((uint8_t*) data)[2];
  packet[(*index) + 0]  = ((uint8_t*) data)[3];
  *index                = *index + sizeof(int32_t);
}

void INT32_merge (const uint8_t* packet, uint16_t* index, int32_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 3];
  ((uint8_t*) data)[1]  = packet[(*index) + 2];
  ((uint8_t*) data)[2]  = packet[(*index) + 1];
  ((uint8_t*) data)[3]  = packet[(*index) + 0];
  *index                = *index + sizeof(int32_t);
}
////////////////////////////////////////////////////////////////////////////////
void UINT32_break (uint8_t* packet, uint16_t* index, const uint32_t* data)
{
  packet[(*index) + 3]  = ((uint8_t*) data)[0];
  packet[(*index) + 2]  = ((uint8_t*) data)[1];
  packet[(*index) + 1]  = ((uint8_t*) data)[2];
  packet[(*index) + 0]  = ((uint8_t*) data)[3];
  *index                = *index + sizeof(uint32_t);
}

void UINT32_merge (const uint8_t* packet, uint16_t* index, uint32_t* data)
{
  ((uint8_t*) data)[0]  = packet[(*index) + 3];
  ((uint8_t*) data)[1]  = packet[(*index) + 2];
  ((uint8_t*) data)[2]  = packet[(*index) + 1];
  ((uint8_t*) data)[3]  = packet[(*index) + 0];
  *index                = *index + sizeof(uint32_t);
}
////////////////////////////////////////////////////////////////////////////////