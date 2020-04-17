#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/bounds.h"
#include "shapes/sphere.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class BoundsTest : public ::testing::Test {
 protected:
  BoundsTest() {};
  ~BoundsTest() {};
};

TEST(BoundsTest, SetsMinMax) {
  Bounds b = Bounds(Point(1, 1, 1), Point(2,2,2));
  EXPECT_EQ(b.maximum(), Point(2, 2, 2));
  EXPECT_EQ(b.minimum(), Point(1, 1, 1));
}

TEST(BoundsTest, Extends) {
  Bounds b = Bounds(Point(0, 0, 0), Point(0, 0, 0));
  b.ExtendToFit(Point(1, 1, 1));
  EXPECT_EQ(b.maximum(), Point(1, 1, 1));
  b.ExtendToFit(Point(-1, -1, -1));
  EXPECT_EQ(b.minimum(), Point(-1, -1, -1));
  b.ExtendToFit(Point(0, -2, 0));
  EXPECT_EQ(b.minimum(), Point(-1, -2, -1));
  b.ExtendToFit(Point(10, 0, 0));
  EXPECT_EQ(b.maximum(), Point(10, 1, 1));
}
