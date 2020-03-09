#include "gtest/gtest.h"

#include "primitives/color.h"

#include <cmath>

class ColorTest : public ::testing::Test {
 protected:
  ColorTest() {};
  ~ColorTest() {};
};

TEST(ColorTest, Basic) {
  const auto c = Color(-0.5, 0.4, 1.7);
  ASSERT_FLOAT_EQ(c.r(), -0.5);
  ASSERT_FLOAT_EQ(c.g(), 0.4);
  ASSERT_FLOAT_EQ(c.b(), 1.7);
}

TEST(ColorTest, Add) {
  const auto c1 = Color(0.9, 0.6, 0.75);
  const auto c2 = Color(0.7, 0.1, 0.25);
  ASSERT_EQ(c1 + c2, Color(1.6, 0.7, 1.0));
}

TEST(ColorTest, Sub) {
  const auto c1 = Color(0.9, 0.6, 0.75);
  const auto c2 = Color(0.7, 0.1, 0.25);
  ASSERT_EQ(c1 - c2, Color(0.2, 0.5, 0.5));
}

TEST(ColorTest, Scale) {
  const auto c = Color(0.2, 0.3, 0.4);
  ASSERT_EQ(c * 2, Color(0.4, 0.6, 0.8));
}

TEST(ColorTest, Multiply) {
  const auto c1 = Color(1.0, 0.2, 0.4);
  const auto c2 = Color(0.9, 1, 0.1);
  ASSERT_EQ(c1 * c2, Color(0.9, 0.2, 0.04)); 
}
