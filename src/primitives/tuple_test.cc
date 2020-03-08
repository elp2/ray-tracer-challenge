#include "gtest/gtest.h"

#include "primitives/tuple.h"

#include <cmath>

class TupleTest : public ::testing::Test {
 protected:
  TupleTest() {};
  ~TupleTest() {};
};

TEST(TupleTest, PointBasic) {
  const auto tuple = new Tuple(4.3, -4.2, 3.1, 1.0);

  EXPECT_FLOAT_EQ(tuple->x(), 4.3);
  EXPECT_FLOAT_EQ(tuple->y(), -4.2);
  EXPECT_FLOAT_EQ(tuple->z(), 3.1);
  EXPECT_FLOAT_EQ(tuple->w(), 1.0);

  EXPECT_TRUE(tuple->IsPoint());
  EXPECT_FALSE(tuple->IsVector());
}

TEST(TupleTest, VectorBasic) {
  const auto tuple = new Tuple(4.3, -4.2, 3.1, 0.0);

  EXPECT_FLOAT_EQ(tuple->x(), 4.3);
  EXPECT_FLOAT_EQ(tuple->y(), -4.2);
  EXPECT_FLOAT_EQ(tuple->z(), 3.1);
  EXPECT_FLOAT_EQ(tuple->w(), 0.0);

  EXPECT_TRUE(tuple->IsVector());
  EXPECT_FALSE(tuple->IsPoint());
}

TEST(TupleTest, CreatePoint) {
  const auto p = TupleFromPoint(4, -4, 3);
  const auto point_tuple = Tuple(4, -4, 3, 1);

  ASSERT_TRUE(p == point_tuple);
}

TEST(TupleTest, CreateVector) {
  const auto v = TupleFromVector(4, -4, 3);
  const auto vector_tuple = Tuple(4, -4, 3, 0);

  ASSERT_TRUE(v == vector_tuple);
}

TEST(TupleTest, AddTwoTuples) {
  const auto a = Tuple(3, -2, 5, 1);
  const auto b = Tuple(-2, 3, 1, 0);

  ASSERT_TRUE(a + b == Tuple(1, 1, 6, 1));
}

TEST(TupleTest, SubTwoTuples) {
  const auto p1 = TupleFromPoint(3, 2, 1);
  const auto p2 = TupleFromPoint(5, 6, 7);

  ASSERT_TRUE(p1 - p2 == TupleFromVector(-2, -4, -6));
}

TEST(TupleTest, SubTwoVectors) {
  const auto p1 = TupleFromVector(3, 2, 1);
  const auto p2 = TupleFromVector(5, 6, 7);

  ASSERT_TRUE(p1 - p2 == TupleFromVector(-2, -4, -6));
}

TEST(TupleTest, SubVectorFromZeroVector) {
  const auto zero = TupleFromVector(0, 0, 0);
  const auto v = TupleFromVector(1, -2, 3);

  ASSERT_TRUE(zero - v == TupleFromVector(-1, 2, -3));
}

TEST(TupleTest, NegateTuple) {
  ASSERT_TRUE(-Tuple(1, -2, 3, -4) == Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, MultiplyTupleByScalar) {
  const auto a = Tuple(1, -2, 3, -4);
  ASSERT_TRUE(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
}

TEST(TupleTest, MultiplyTupleByFraction) {
  const auto a = Tuple(1, -2, 3, -4);
  ASSERT_TRUE(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
}

TEST(TupleTest, DivideTuple) {
  const auto a = Tuple(1, -2, 3, -4);
  ASSERT_TRUE(a / 2 == Tuple(0.5, -1, 1.5, -2));
  ASSERT_TRUE(a / 2 == a * 0.5);
}

TEST(TupleTest, UnitVectorMagnitudes) {
  auto x = TupleFromVector(1, 0, 0);
  auto y = TupleFromVector(0, 1, 0);
  auto z = TupleFromVector(0, 0, 1);
  ASSERT_FLOAT_EQ(x.Magnitude(), 1);
  ASSERT_FLOAT_EQ(y.Magnitude(), 1);
  ASSERT_FLOAT_EQ(z.Magnitude(), 1);
}

TEST(TupleTest, UnitVectorOpposing) {
  const auto x = TupleFromVector(1, 2, 3);
  const auto y = TupleFromVector(-1, -2, -3);
  ASSERT_FLOAT_EQ(x.Magnitude(), y.Magnitude());
  ASSERT_FLOAT_EQ(y.Magnitude(), std::sqrt(14));
}

TEST(TupleTest, Normalized) {
  const auto x = TupleFromVector(4, 0, 0);
  ASSERT_TRUE(x.Normalized() == TupleFromVector(1, 0, 0));
}

TEST(TupleTest, Normalize123) {
  const auto v = TupleFromVector(1, 2, 3);
  ASSERT_TRUE(v.Normalized() == TupleFromVector(0.26726, 0.53452, 0.80178));
  ASSERT_FLOAT_EQ(v.Normalized().Magnitude(), 1);
}

TEST(TupleTest, DotProduct) {
  const auto a = TupleFromVector(1, 2, 3);
  const auto b = TupleFromVector(2, 3, 4);
  ASSERT_FLOAT_EQ(a.Dot(b), 20);
}

TEST(TupleTest, CrossProduct) {
  const auto a = TupleFromVector(1, 2, 3);
  const auto b = TupleFromVector(2, 3, 4);

  ASSERT_TRUE(a.Cross(b) == TupleFromVector(-1, 2, -1));
  ASSERT_TRUE(b.Cross(a) == TupleFromVector(1, -2, 1));
}
