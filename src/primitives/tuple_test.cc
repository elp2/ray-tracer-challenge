#include "gtest/gtest.h"

#include "primitives/tuple.h"

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