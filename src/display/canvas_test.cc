#include "gtest/gtest.h"

#include "display/canvas.h"

#include <cmath>

class CanvasTest : public ::testing::Test {
 protected:
  CanvasTest() {};
  ~CanvasTest() {};
};

TEST(CanvasTest, StartsBlack) {
  Canvas canvas = Canvas(10, 20);
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      ASSERT_EQ(Color(0,0,0), canvas.PixelAt(x, y));
    }
  }
}

TEST(CanvasTest, WriteRead) {
  Canvas canvas = Canvas(10, 20);  
  Color red = Color(1, 0, 0);
  canvas.WritePixel(red, 2, 3);
  ASSERT_EQ(red, canvas.PixelAt(2, 3));
}
