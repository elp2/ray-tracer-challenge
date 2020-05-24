#include "gtest/gtest.h"

#include "images/crc.h"

#include <bitset>
#include <iostream>

class CRCTest : public ::testing::Test {
 protected:
  CRCTest() {};
  ~CRCTest() {};
};

TEST(CRCTest, Simple) {
  uint8_t data[1] = { 0 };
  uint32_t crc = calculate_crc(data, 1);
  ASSERT_EQ(crc, 0xD202EF8D);
}

TEST(CRCTest, Longer) {
  uint8_t data[9] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };
  uint32_t crc = calculate_crc(data, 9);

  ASSERT_EQ(crc, 0xCBF43926);
}
