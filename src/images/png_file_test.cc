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

TEST(PNGFileTest, FilterType1Simple) {
  // SUB: Add a delta onto the previous pixel.
  uint8_t data[] = {1, 255, 255, 255, 0, 0, 0};
  std::vector<Color> expected = std::vector<Color> {
    Color(1, 1, 1), Color(1, 1, 1)
  };

  PNGFile *png = new PNGFile(2, 1);
  png->ParsePixels(data, 7);

  std::vector<Color> *pixels = png->pixels();
  ASSERT_EQ(expected.size(), pixels->size());
  for (int i = 0; i < pixels->size(); ++i) {
    EXPECT_EQ((*pixels)[i], expected[i]) << "Failure at " << i;
  }
}

TEST(PNGFileTest, FilterType1Add) {
  // SUB: Add a delta from the previous pixel.
  uint8_t data[] = {1, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
  float a = 0.0;
  float b = 100.0 / 255.0;
  float c = 200.0 / 255.0;
  float d = (300 % 256) / 255.0;
  std::vector<Color> expected = std::vector<Color> {
    Color(a, a, a), Color(b, b, b), Color(c, c, c), Color(d, d, d),
  };

  PNGFile *png = new PNGFile(4, 1);
  png->ParsePixels(data, 13);

  std::vector<Color> *pixels = png->pixels();
  ASSERT_EQ(expected.size(), pixels->size());
  for (int i = 0; i < pixels->size(); ++i) {
    EXPECT_EQ((*pixels)[i], expected[i]) << "Failure at " << i;
  }
}

TEST(PNGFileTest, FilterType2Simple) {
  // SUB: Add a delta from the pixel in the previous row.
  uint8_t data[] = {
    0, 255, 255, 255, 255, 255, 255,
    2, 0, 0, 0, 0, 0, 0,
  };
  std::vector<Color> expected = std::vector<Color> {
    Color(1, 1, 1), Color(1, 1, 1),
    Color(1, 1, 1), Color(1, 1, 1),
  };

  PNGFile *png = new PNGFile(2, 2);
  png->ParsePixels(data, 14);

  std::vector<Color> *pixels = png->pixels();
  ASSERT_EQ(expected.size(), pixels->size());
  for (int i = 0; i < pixels->size(); ++i) {
    EXPECT_EQ((*pixels)[i], expected[i]) << "Failure at " << i;
  }
}

TEST(PNGFileTest, FilterType0) {
  uint8_t data[] = {0, 255, 255, 255, 0, 0, 0, 255, 255, 255,
                   0, 0, 0, 0, 255, 255, 255, 0, 0, 0,
                   0, 255, 255, 255, 0, 0, 0, 255, 255, 255};
  std::vector<Color> expected = std::vector<Color> {
    Color(1, 1, 1), Color(0, 0, 0), Color(1, 1, 1),
    Color(0, 0, 0), Color(1, 1, 1), Color(0, 0, 0),
    Color(1, 1, 1), Color(0, 0, 0), Color(1, 1, 1),
  };

  PNGFile *png = new PNGFile(3, 3);
  png->ParsePixels(data, 30);

  std::vector<Color> *pixels = png->pixels();
  ASSERT_EQ(expected.size(), pixels->size());
  for (int i = 0; i < pixels->size(); ++i) {
    EXPECT_EQ((*pixels)[i], expected[i]) << "Failure at " << i;
  }
}
