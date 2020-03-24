#include "gtest/gtest.h"

#include "primitives/matrix.h"
#include "primitives/ray.h"
#include "primitives/tuple.h"
#include "primitives/transformation.h"

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

TEST(RayTest, TranslateRay) {
  Ray r = Ray(TupleFromPoint(1, 2, 3), TupleFromVector(0, 1, 0));
  Matrix m = Translation(3, 4, 5);
  Ray r2 = r.Transform(m);

  ASSERT_EQ(r2.Origin(), TupleFromPoint(4, 6, 8));
  ASSERT_EQ(r2.Direction(), TupleFromVector(0, 1, 0));
}

TEST(RayTest, ScaleRay) {
  Ray r = Ray(TupleFromPoint(1, 2, 3), TupleFromVector(0, 1, 0));
  Matrix m = Scaling(2, 3, 4);
  Ray r2 = r.Transform(m);

  ASSERT_EQ(r2.Origin(), TupleFromPoint(2, 6, 12));
  ASSERT_EQ(r2.Direction(), TupleFromVector(0, 3, 0));
}
