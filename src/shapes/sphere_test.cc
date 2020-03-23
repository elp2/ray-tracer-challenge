#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/sphere.h"
#include "primitives/tuple.h"

#include <vector>

class SphereTest : public ::testing::Test {
 protected:
  SphereTest() {};
  ~SphereTest() {};
};

TEST(SphereTest, IntersectsTwoPointsStraightOn) {
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<Intersection> xs = s.Intersections(r);

  ASSERT_EQ(2, xs.size());
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 6.0);
}
