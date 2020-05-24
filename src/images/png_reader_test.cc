#include "gtest/gtest.h"

#include "images/png_reader.h"
#include "images/png_writer.h"

#include <bitset>
#include <iostream>

class PNGReaderTest : public ::testing::Test {
 protected:
  PNGReaderTest() {};
  ~PNGReaderTest() {};
};

TEST(PNGReaderTest, ReadsHeader) {
  PNGReader reader = PNGReader();
  PNGFile png = reader.ReadFile("red_dot.png");
  ASSERT_EQ(png.w, 1);
  ASSERT_EQ(png.h, 1);
}
