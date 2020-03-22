#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "primitives/tuple.h"

class RayTest : public ::testing::Test {
 protected:
  RayTest() {};
  ~RayTest() {};
};

TEST(RayTest, OriginDirection) {
  Tuple origin = TupleFromPoint(1, 2, 3);
  Tuple direction = TupleFromVector(4, 5, 6);
  Ray r = Ray(origin, direction);

  ASSERT_EQ(r.Origin(), origin);
  ASSERT_EQ(r.Direction(), direction);
}

TEST(RayTest, Position) {
  Ray r = Ray(TupleFromPoint(2, 3, 4), TupleFromVector(1, 0, 0));
  ASSERT_EQ(r.Position(0), TupleFromPoint(2, 3, 4));
  ASSERT_EQ(r.Position(1), TupleFromPoint(3, 3, 4));
  ASSERT_EQ(r.Position(-1), TupleFromPoint(1, 3, 4));
  ASSERT_EQ(r.Position(2.5), TupleFromPoint(4.5, 3, 4));
}
