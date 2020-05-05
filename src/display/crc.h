#ifndef RTC_DISPLAY_CRC_H
#define RTC_DISPLAY_CRC_H

#include <stdint.h>

uint32_t calculate_crc(const void *data, int length);

#endif    // RTC_DISPLAY_CRC_H
