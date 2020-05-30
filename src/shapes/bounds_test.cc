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

TEST(BoundsTest, UnitTranslation) {
  Bounds b = Bounds(Point(-1, 0, -3), Point(1, 2, -1));
  Matrix transform = b.UnitifyTransform(true, false, false);
  ASSERT_EQ(transform, Translation(0, -1, 2));
}

TEST(BoundsTest, UnitTranslationRight) {
  Bounds b = Bounds(Point(1, 2, -1), Point(3, 4, 1));
  Matrix transform = b.UnitifyTransform(true, false, false);
  ASSERT_EQ(transform, Translation(-2, -3, 0));
}

TEST(BoundsTest, UnitScaling) {
  Bounds b = Bounds(Point(-2, -2, -2), Point(2, 2, 2));
  Matrix transform = b.UnitifyTransform(true, false, false);
  ASSERT_EQ(transform, Scaling(0.5, 0.5, 0.5));
}

TEST(BoundsTest, UnitifyXY) {
  Bounds b = Bounds(Point(-4, -2, -2), Point(4, 2, 2));
  Matrix transform = b.UnitifyTransform(true, true, false);
  ASSERT_EQ(transform, Scaling(0.25, 0.25, 0.25));
}

TEST(BoundsTest, UnitifyXZ) {
  Bounds b = Bounds(Point(-2, -2, -4), Point(2, 2, 4));
  Matrix transform = b.UnitifyTransform(true, false, true);
  ASSERT_EQ(transform, Scaling(0.25, 0.25, 0.25));
}

TEST(BoundsTest, ScaleMove) {
  Bounds b = Bounds(Point(4, 4, 4), Point(8, 8, 8));
  Matrix transform = b.UnitifyTransform(true, false, true);
  ASSERT_EQ(transform, Scaling(0.5, 0.5, 0.5) * Translation(-6, -6, -6));
}

TEST(BoundsTest, UnitUntouched) {
  Bounds b = Bounds(Point(-1, -1, -1), Point(1, 1, 1));
  Matrix transform = b.UnitifyTransform(true, false, true);
  ASSERT_EQ(transform, IdentityMatrix(4));
}
