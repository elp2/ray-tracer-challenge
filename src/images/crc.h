#ifndef RTC_DISPLAY_CRC_H
#define RTC_DISPLAY_CRC_H

#include <stdint.h>
#include <string>

uint32_t calculate_crc(const void *data, int length);

uint32_t calculate_png_crc(const std::string &type, const void *data, const int length);

#endif    // RTC_DISPLAY_CRC_H
