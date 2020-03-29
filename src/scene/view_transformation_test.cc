#include "gtest/gtest.h"

#include <vector>

#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "scene/view_transformation.h"

class ViewTransformationTest : public ::testing::Test {
 protected:
  ViewTransformationTest() {};
  ~ViewTransformationTest() {};
};

TEST(ViewTransformationTest, DefaultOrientation) {
  Tuple from = Point(0.0, 0.0, 0.0);
  Tuple to = Point(0.0, 0.0, -1.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  Matrix t = ViewTransformation(from, to, up);
  ASSERT_EQ(t, IdentityMatrix(4));
}

TEST(ViewTransformationTest, PositiveZDirection) {
  Tuple from = Point(0.0, 0.0, 0.0);
  Tuple to = Point(0.0, 0.0, 1.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  Matrix t = ViewTransformation(from, to, up);
  ASSERT_EQ(t, Scaling(-1.0, 1.0, -1.0));
}

TEST(ViewTransformationTest, MovesWorld) {
  Tuple from = Point(0.0, 0.0, 8.0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  Matrix t = ViewTransformation(from, to, up);
  ASSERT_EQ(t, Translation(0.0, 0.0, -8.0));
}

TEST(ViewTransformationTest, Arbitrary) {
  Tuple from = Point(1.0, 3.0, 2.0);
  Tuple to = Point(4.0, -2.0, 8.0);
  Tuple up = Vector(1.0, 1.0, 0.0);
  Matrix t = ViewTransformation(from, to, up);
  Matrix expected = Matrix(4, 4, std::vector<float> {
    -0.50709, 0.50709, 0.67612, -2.36643,
    0.76772, 0.60609, 0.12122, -2.82843,
    -0.35857, 0.59761, -0.71714, 0.00000,
    0.00000, 0.00000, 0.00000, 1.00000
  });
  ASSERT_EQ(t, expected);
}
