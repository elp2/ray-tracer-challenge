#include "gtest/gtest.h"

#include "images/png_file.h"
#include "images/png_reader.h"
#include "images/png_writer.h"

#include <bitset>
#include <iostream>

class PNGFileTest : public ::testing::Test {
 protected:
  PNGFileTest() {};
  ~PNGFileTest() {};
};

TEST(PNGFileTest, ConsolidatesMultipleIDATs) {
  uint8_t data[] = {0, 255, 255, 255, 0, 0, 0, 255, 255, 255,
                   0, 0, 0, 0, 255, 255, 255, 0, 0, 0,
                   0, 255, 255, 255, 0, 0, 0, 255, 255, 255};
  std::vector<Color> expected = std::vector<Color> {
    Color(1, 1, 1), Color(0, 0, 0), Color(1, 1, 1),
    Color(0, 0, 0), Color(1, 1, 1), Color(0, 0, 0),
    Color(1, 1, 1), Color(0, 0, 0), Color(1, 1, 1),
  };

  for (int a = -3; a <= 3; ++a) {
    for (int b = -3; b <= 3; ++b) {
      PNGFile *png = new PNGFile();
      png->set_height(3);
      png->set_width(3);

      int segment1 = 10 + a;
      // Call ParsePixels directly so we don't have to bother compressing.
      png->ParsePixels(data, segment1);
      int segment2 = (20 + b) - (segment1);
      png->ParsePixels(data + segment1, segment2);
      int segment3 = 30 - segment2 - segment1;
      png->ParsePixels(data + segment1 + segment2, segment3);

      std::vector<Color> *pixels = png->pixels();
      ASSERT_EQ(expected.size(), pixels->size());
    }
  }


}
