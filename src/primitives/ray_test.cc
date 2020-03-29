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
  Tuple origin = Point(1, 2, 3);
  Tuple direction = Vector(4, 5, 6);
  Ray r = Ray(origin, direction);

  ASSERT_EQ(r.Origin(), origin);
  ASSERT_EQ(r.Direction(), direction);
}

TEST(RayTest, Position) {
  Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
  ASSERT_EQ(r.Position(0), Point(2, 3, 4));
  ASSERT_EQ(r.Position(1), Point(3, 3, 4));
  ASSERT_EQ(r.Position(-1), Point(1, 3, 4));
  ASSERT_EQ(r.Position(2.5), Point(4.5, 3, 4));
}

TEST(RayTest, TranslateRay) {
  Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = Translation(3, 4, 5);
  Ray r2 = r.Transform(m);

  ASSERT_EQ(r2.Origin(), Point(4, 6, 8));
  ASSERT_EQ(r2.Direction(), Vector(0, 1, 0));
}

TEST(RayTest, ScaleRay) {
  Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = Scaling(2, 3, 4);
  Ray r2 = r.Transform(m);

  ASSERT_EQ(r2.Origin(), Point(2, 6, 12));
  ASSERT_EQ(r2.Direction(), Vector(0, 3, 0));
}
