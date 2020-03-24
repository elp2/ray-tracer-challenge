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
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 6.0);
}

TEST(SphereTest, IntersectsAtTangent) {
  Ray r = Ray(TupleFromPoint(0, 1, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), 5.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 5.0);
}

TEST(SphereTest, MissesSphere) {
  Ray r = Ray(TupleFromPoint(0, 2, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(0, xs.Size());
}

TEST(SphereTest, OriginatesInSphere) {
  Ray r = Ray(TupleFromPoint(0, 0, 0), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), -1.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 1.0);
}

TEST(SphereTest, SphereBehindRay) {
  Ray r = Ray(TupleFromPoint(0, 0, 5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), -6.0);
  ASSERT_FLOAT_EQ(xs[1].T(), -4.0);
}

TEST(SphereTest, ObjectSetOnIntersection) {
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_EQ(xs[0].Object(), &s);
  ASSERT_EQ(xs[1].Object(), &s);
}
