#include "gtest/gtest.h"

#include "primitives/matrix.h"

class MatrixTest : public ::testing::Test {
 protected:
  MatrixTest() {};
  ~MatrixTest() {};
};

TEST(MatrixTest, SetGet) {
  Matrix m = Matrix(3, 4);
  ASSERT_FLOAT_EQ(m(0, 0), 0.0);

  m.Set(1.0, 1, 1);
  ASSERT_FLOAT_EQ(m(1, 1), 1.0);
}

TEST(MatrixTest, TwoByTwo) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, ThreeByThree) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, Equal) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, NotEqual) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MultiplyMatrix) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MultiplyTuple) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MultiplyIdentity) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MultiplyTupleItentity) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, Transpose) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, Invert) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, SubmatrixOf3x3Is2x2) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, SubmatrixOf4x4Is3x3) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MinorOf3x3) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, CofactorOf3x3) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, DeterminantOf3x3) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, DeterminantOf4x4) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, IsInvertable) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, NotInvertable) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, InverseOfMatrix) {
  ASSERT_FALSE(true); // TODO.
}

TEST(MatrixTest, MultiplyProductByInverse) {
  ASSERT_FALSE(true); // TODO.
}
