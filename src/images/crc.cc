#include "images/crc.h"

#include <bitset>
#include <iostream>

const uint32_t POLYNOMIAL = 0x04C11DB7;
// Avoid processing 32 bits of 0's at end.
const uint32_t CRC_INIT = 0x46AF6449;
const uint32_t CRC_XOR = 0xFFFFFFFF;
const uint32_t CRC_HIGH_BIT = 1 << 31;

uint32_t reflect(uint32_t word, int lower_bits) {
  uint32_t reflected = 0;
  uint32_t orer = 1;
  for (uint32_t i = 1 << (lower_bits - 1); i; i >>= 1) {
    if (i & word) {
      reflected |= orer;
    }
    orer <<= 1;
  }
  return reflected;
}

uint32_t calculate_crc(const void *data, int length) {
  uint32_t crc = CRC_INIT;
  uint8_t *udata = (uint8_t *)data;
  for (int byte_idx = 0; byte_idx < length; ++byte_idx) {
    uint32_t byte = reflect(udata[byte_idx], 8);

    for (uint8_t test_bit = 0x80; test_bit; test_bit >>= 1) {
      bool high_bit_set = crc & CRC_HIGH_BIT;
      crc <<= 1;
      if (byte & test_bit) {
        crc |= 1;
      }
      if (high_bit_set) {
        crc ^= POLYNOMIAL;
      }
    }
  }

  for (int bit_num = 0; bit_num < 32; bit_num++) {
    bool high_bit_set = crc & CRC_HIGH_BIT;
    crc <<= 1;
    if (high_bit_set) {
      crc ^= POLYNOMIAL;
    }
  }

  crc = reflect(crc, 32);
  return crc ^ CRC_XOR;
}
