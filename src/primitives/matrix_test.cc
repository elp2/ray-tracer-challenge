#include "gtest/gtest.h"

#include "primitives/matrix.h"
#include "primitives/tuple.h"

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

TEST(MatrixTest, Equal) {
  std::vector<float> values = {1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 8, 7, 6,
                               5, 4, 3, 2};
  Matrix a = Matrix(4, 4, values);
  Matrix b = Matrix(4, 4, values);
  ASSERT_EQ(a, b);
}

TEST(MatrixTest, NotEqual) {
  std::vector<float> values = {1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 8, 7, 6,
                               5, 4, 3, 2};
  Matrix a = Matrix(4, 4, values);

  for (int i = 0; i < 16; ++i) {
    float orig = values[i];
    values[i] = 99;
    Matrix b = Matrix(4, 4, values);
    ASSERT_NE(a, b);
    values[i] = orig;
  }

  Matrix b = Matrix(4, 4, values);
  ASSERT_EQ(a, b);
}

TEST(MatrixTest, MultiplyMatrix) {
  std::vector<float> avalues = {1, 2, 3, 4,
                                5, 6, 7, 8,
                                9, 8, 7, 6,
                                5, 4, 3, 2};
  Matrix a = Matrix(4, 4, avalues);
  std::vector<float> bvalues = {-2, 1, 2, 3,
                                3, 2, 1, -1,
                                4, 3, 6, 5,
                                1, 2, 7, 8};
  Matrix b = Matrix(4, 4, bvalues);
  Matrix mult = a * b;

  std::vector<float> expected = {20, 22, 50, 48,
                                 44, 54, 114, 108,
                                 40, 58, 110, 102,
                                 16, 26, 46, 42};
  Matrix exp = Matrix(4, 4, expected);
  ASSERT_EQ(mult, exp);
}

TEST(MatrixTest, MultiplyTuple) {
  std::vector<float> values = {1, 2, 3, 4,
                               2, 4, 4, 2,
                               8, 6, 4, 1,
                               0, 0, 0, 1};
  Matrix m = Matrix(4, 4, values);

  Tuple t = Tuple(1, 2, 3, 1);
  Tuple ret = m * t;
  ASSERT_EQ(Tuple(18, 24, 33, 1), ret);
}

TEST(MatrixTest, MultiplyIdentity) {
  std::vector<float> values = {1, 2, 3, 4,
                               2, 4, 4, 2,
                               8, 6, 4, 1,
                               0, 0, 0, 1};
  Matrix m = Matrix(4, 4, values);
  ASSERT_EQ(m,  m * IdentityMatrix(4));
}

TEST(MatrixTest, MultiplyTupleIdentity) {
  Tuple t = Tuple(1, 2, 3, 1);
  ASSERT_EQ(t, IdentityMatrix(4) * t);
}

TEST(MatrixTest, Transpose) {
  Matrix m = Matrix(4, 4, std::vector<float> { 0, 9, 3, 0,
                                               9, 8, 0, 8,
                                               1, 8, 5, 3,
                                               0, 0, 5, 8 });
  Matrix t = Matrix(4, 4, std::vector<float> { 0, 9, 1, 0,
                                               9, 8, 8, 0,
                                               3, 0, 5, 5,
                                               0, 8, 3, 8 });
  ASSERT_EQ(m.Transpose(), t);
}

TEST(MatrixTest, DeterminantOf2x2) {
  Matrix m = Matrix(2, 2, std::vector<float> { 1, 5,
                                              -3, 2 });
  ASSERT_FLOAT_EQ(m.Determinant(), 17);
}

TEST(MatrixTest, SubmatrixOf3x3Is2x2) {
  Matrix three = Matrix(3, 3, std::vector<float> { 1, 5, 0,
                                                  -3, 2, 7,
                                                  0, 6, -3 });
  Matrix sub = Matrix(2, 2, std::vector<float> { -3, 2,
                                                  0, 6 });
  ASSERT_EQ(three.SubMatrix(0, 2), sub);
}

TEST(MatrixTest, SubmatrixOf4x4Is3x3) {
  Matrix fourx4 = Matrix(4, 4, std::vector<float> { -6, 1, 1, 6,
                                                    -8, 5, 8, 6,
                                                    -1, 0, 8, 2,
                                                    -7, 1, -1, 1 });
  Matrix threex3 = Matrix(3, 3, std::vector<float> { -6, 1, 6,
                                                      -8, 8, 6,
                                                      -7, -1, 1 });
  ASSERT_EQ(fourx4.SubMatrix(2, 1), threex3);
}

TEST(MatrixTest, MinorOf3x3) {
  Matrix three = Matrix(3, 3, std::vector<float> { 3, 5, 0,
                                                   2, -1, -7,
                                                   6, -1, 5 });
  ASSERT_FLOAT_EQ(three.Minor(1, 0), 25);
}

TEST(MatrixTest, CofactorOf3x3) {
  Matrix three = Matrix(3, 3, std::vector<float> { 3, 5, 0,
                                                   2, -1, -7,
                                                   6, -1, 5 });
  ASSERT_FLOAT_EQ(three.Minor(0, 0), -12);
  ASSERT_FLOAT_EQ(three.Cofactor(0, 0), -12);
  ASSERT_FLOAT_EQ(three.Minor(1, 0), 25);
  ASSERT_FLOAT_EQ(three.Cofactor(1, 0), -25);
}
/*
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