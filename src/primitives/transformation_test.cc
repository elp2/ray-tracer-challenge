#include "gtest/gtest.h"

#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>

class TransformationTest : public ::testing::Test {
 protected:
  TransformationTest() {};
  ~TransformationTest() {};
};

TEST(TransformationTest, MultiplyTranslation) {
  Matrix transform = Translation(5, -3, 2);
  Tuple p = TupleFromPoint(-3, 4, 5);
  ASSERT_EQ(TupleFromPoint(2, 1, 7), transform * p);
}

TEST(TransformationTest, MultiplyTranslationInverse) {
  Matrix transform = Translation(5, -3, 2);
  Matrix inverse = transform.Inverse();
  Tuple p = TupleFromPoint(-3, 4, 5);
  ASSERT_EQ(TupleFromPoint(-8, 7, 3), inverse * p);
}

TEST(TransformationTest, TranslationDoesNotAffectVectors) {
  Matrix transform = Translation(5, -3, 2);
  Tuple v = TupleFromVector(-3, 4, 5);
  ASSERT_EQ(v, transform * v);
}

TEST(TransformationTest, ScalePoint) {
  Matrix transform = Scaling(2, 3, 4);
  Tuple p = TupleFromPoint(-4, 6, 8);
  ASSERT_EQ(TupleFromPoint(-8, 18, 32), transform * p);
}

TEST(TransformationTest, ScaleVector) {
  Matrix transform = Scaling(2, 3, 4);
  Tuple v = TupleFromVector(-4, 6, 8);
  ASSERT_EQ(TupleFromVector(-8, 18, 32), transform * v);
}

TEST(TransformationTest, ScaleInverse) {
  Matrix transform = Scaling(2, 3, 4);
  Tuple v = TupleFromVector(-4, 6, 8);
  Matrix inverse = transform.Inverse();
  ASSERT_EQ(TupleFromVector(-2, 2, 2), inverse * v);
}

TEST(TransformationTest, ReflectionScaleUsingNegativeValue) {
  Matrix transform = Scaling(-1, 1, 1);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(-2, 3, 4), transform * p);
}

TEST(TransformationTest, RotationX) {
  Matrix half_quarter = RotationX(M_PI / 4);
  Matrix full_quarter = RotationX(M_PI / 2);  
  Tuple p = TupleFromPoint(0, 1, 0);

  ASSERT_EQ(TupleFromPoint(0, sqrt(2) / 2, sqrt(2) / 2), half_quarter * p);
  ASSERT_EQ(TupleFromPoint(0, 0, 1), full_quarter * p);
}

TEST(TransformationTest, RotationXInverse) {
  Matrix half_quarter = RotationX(M_PI / 4);
  Matrix full_minus_half_quarter = RotationX(2 * M_PI - M_PI / 4);
  Matrix inverse = half_quarter.Inverse();
  Tuple p = TupleFromPoint(0, 1, 0);

  ASSERT_EQ(TupleFromPoint(0, sqrt(2) / 2, -sqrt(2) / 2), inverse * p);
  ASSERT_EQ(inverse * p, full_minus_half_quarter * p);
}

TEST(TransformationTest, RotationY) {
  Matrix half_quarter = RotationY(M_PI / 4);
  Matrix full_quarter = RotationY(M_PI / 2);  
  Tuple p = TupleFromPoint(0, 0, 1);

  ASSERT_EQ(TupleFromPoint(sqrt(2) / 2, 0, sqrt(2) / 2), half_quarter * p);
  ASSERT_EQ(TupleFromPoint(1, 0, 0), full_quarter * p);
}

TEST(TransformationTest, RotationZ) {
  Matrix half_quarter = RotationZ(M_PI / 4);
  Matrix full_quarter = RotationZ(M_PI / 2);  
  Tuple p = TupleFromPoint(0, 1, 0);

  ASSERT_EQ(TupleFromPoint(-sqrt(2) / 2, sqrt(2) / 2, 0), half_quarter * p);
  ASSERT_EQ(TupleFromPoint(-1, 0, 0), full_quarter * p);
}

TEST(TransformationTest, ShearingXY) {
  Matrix transform = Shearing(1, 0, 0, 0, 0, 0);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(5, 3, 4), transform * p);
}

TEST(TransformationTest, ShearingXZ) {
  Matrix transform = Shearing(0, 1, 0, 0, 0, 0);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(6, 3, 4), transform * p);
}

TEST(TransformationTest, ShearingYX) {
  Matrix transform = Shearing(0, 0, 1, 0, 0, 0);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(2, 5, 4), transform * p);
}

TEST(TransformationTest, ShearingYZ) {
  Matrix transform = Shearing(0, 0, 0, 1, 0, 0);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(2, 7, 4), transform * p);
}

TEST(TransformationTest, ShearingZX) {
  Matrix transform = Shearing(0, 0, 0, 0, 1, 0);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(2, 3, 6), transform * p);
}

TEST(TransformationTest, ShearingZY) {
  Matrix transform = Shearing(0, 0, 0, 0, 0, 1);
  Tuple p = TupleFromPoint(2, 3, 4);
  ASSERT_EQ(TupleFromPoint(2, 3, 7), transform * p);
}
