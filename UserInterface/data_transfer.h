#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

#include "stm32f0xx.h"
#define SYNC_BYTE1              0x75
#define SYNC_BYTE2              0x1B
#define PACKET_SIZE_EXCEPT_DATA 4
#define PACKET_DATA_SIZE        50
#define PACKET_SIZE_WITH_CRC    (PACKET_SIZE_EXCEPT_DATA + 2)

enum data_capture_status
{
  CAPTURE_SYNC1 = 0,
  CAPTURE_SYNC2,
  CAPTURE_PACKET_TYPE,
  CAPTURE_DATA_SIZE,
  CAPTURE_DATA,
  CAPTURE_CRC1,
  CAPTURE_CRC2
};

enum package_types
{
  REGISTER_1,
  REGISTER_2,
  REGISTER_3,
  REGISTER_4,
  REGISTER_5,
  REGISTER_6,
  REGISTER_7,
  REGISTER_8,
  REGISTER_9,
  REGISTER_10
};

typedef struct
{
  uint32_t      regValue;
  
} reg_32;

typedef struct
{
  uint8_t       sync_byte1;
  uint8_t       sync_byte2;
  uint8_t       packet_type;
  uint8_t       data_size;
  uint8_t       data[PACKET_DATA_SIZE];
  uint8_t       crc_high;
  uint8_t       crc_low;
} data_packet_t;

typedef struct
{
  uint8_t       data_capture_status;
  uint8_t       data_counter;
  data_packet_t data_packet;
  uint32_t      incoming_byte_number;
  uint32_t      faultless_packet_number;
  uint32_t      faulty_packet_number;
} captured_packet_t;


void capture_data(captured_packet_t* captured_packet, const uint8_t* captured_data, const uint32_t captured_data_size);
void pack_data(data_packet_t* data_packet);
void resolve_cu_data_packet(const data_packet_t *data_packet, reg_32 *data);
void resolve_packet(const data_packet_t *data_packet);
void sendDataToInterface(uint8_t packet_type, const uint32_t* regValue);

#endif