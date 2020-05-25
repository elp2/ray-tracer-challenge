#include "gtest/gtest.h"

#include "images/png_file.h"
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
  // TODO: Break this into bytes.
  PNGFile *png = reader.ReadFile("red_dot.png");
  ASSERT_EQ(png->width(), 1);
  ASSERT_EQ(png->height(), 1);
}

TEST(PNGReaderTest, ReadsSingleIDAT) {
  PNGReader reader = PNGReader();
  PNGFile *png = reader.ReadFile("red_dot.png");
  std::vector<Color> *pixels = png->pixels();
  ASSERT_EQ(pixels->size(), 1);
  ASSERT_EQ(Color(1, 0, 0), (*pixels)[0]);
}
