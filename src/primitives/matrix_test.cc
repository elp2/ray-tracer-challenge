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

TEST(MatrixTest, FourByFour) {
  std::vector<float> values = {1, 2, 3, 4,
                        5.5, 6.5, 7.5, 8.5,
                        9, 10, 11, 12,
                        13.5, 14.5, 15.5, 16.5};
  Matrix m = Matrix(4, 4, values);
  ASSERT_FLOAT_EQ(m(0, 0), 1);
  ASSERT_FLOAT_EQ(m(1, 0), 5.5);
  ASSERT_FLOAT_EQ(m(0, 3), 4);
  ASSERT_FLOAT_EQ(m(1, 2), 7.5);
  ASSERT_FLOAT_EQ(m(2, 2), 11);
  ASSERT_FLOAT_EQ(m(3, 0), 13.5);
  ASSERT_FLOAT_EQ(m(3, 2), 15.5);
}

TEST(MatrixTest, TwoByTwo) {
  std::vector<float> values = {-3, 5,
                                1, -2};
  Matrix m = Matrix(2, 2, values);
  ASSERT_FLOAT_EQ(m(0, 0), -3);
  ASSERT_FLOAT_EQ(m(0, 1), 5);
  ASSERT_FLOAT_EQ(m(1, 0), 1);
  ASSERT_FLOAT_EQ(m(1, 1), -2);
}

TEST(MatrixTest, ThreeByThree) {
  std::vector<float> values = {-3, 5, 0,
                                1, -2, -7,
                                0, 1, 1};
  Matrix m = Matrix(3, 3, values);
  ASSERT_FLOAT_EQ(m(0, 0), -3);
  ASSERT_FLOAT_EQ(m(1, 1), -2);  
  ASSERT_FLOAT_EQ(m(2, 2), 1);
}
/*
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
*/