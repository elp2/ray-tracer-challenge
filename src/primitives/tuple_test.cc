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
