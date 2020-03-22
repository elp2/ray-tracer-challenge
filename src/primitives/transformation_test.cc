#include "gtest/gtest.h"

#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

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
