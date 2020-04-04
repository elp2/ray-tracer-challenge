#include "gtest/gtest.h"

#include <math.h>

#include "primitives/ray.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/plane.h"
#include "shapes/shape.h"

class PlaneTest : public ::testing::Test {
 protected:
  PlaneTest() {};
  ~PlaneTest() {};
};

TEST(PlaneTest, NormalConstantEverywhere) {
  Plane p = Plane();
  Tuple n1 = p.Normal(Point(0.0, 0.0, 0.0));
  Tuple n2 = p.Normal(Point(10.0, 0.0, -10.0));
  Tuple n3 = p.Normal(Point(-5.0, 0.0, 150.0));
  ASSERT_EQ(n1, Vector(0.0, 1.0, 0.0));
  ASSERT_EQ(n2, Vector(0.0, 1.0, 0.0));
  ASSERT_EQ(n3, Vector(0.0, 1.0, 0.0));
}

TEST(PlaneTest, ParallelRayDoesntIntersect) {
  Plane p = Plane();
  Ray r = Ray(Point(0.0, 10.0, 0.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = p.Intersect(r);
  ASSERT_FALSE(xs.Hit().has_value());
}

TEST(PlaneTest, CoplanarRayDoesntExist) {
  Plane p = Plane();
  Ray r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = p.Intersect(r);
  ASSERT_FALSE(xs.Hit().has_value());
}

TEST(PlaneTest, RayIntersectsPlaneFromAbove) {
  Plane p = Plane();
  Ray r = Ray(Point(0.0, 1.0, 0.0), Vector(0.0, -1.0, 0.0));
  Intersections xs = p.Intersect(r);
  ASSERT_EQ(xs.Size(), 1);
  Intersection hit = xs.Hit().value();
  ASSERT_EQ(hit.T(), 1.0);
  ASSERT_EQ(hit.Object(), &p);
}

TEST(PlaneTest, RayIntersectsPlaneFromBelow) {
  Plane p = Plane();
  Ray r = Ray(Point(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0));
  Intersections xs = p.Intersect(r);
  ASSERT_EQ(xs.Size(), 1);
  Intersection hit = xs.Hit().value();
  ASSERT_EQ(hit.T(), 1.0);
  ASSERT_EQ(hit.Object(), &p);
}

TEST(PlaneTest, RayIntersectsPlaneFromSide) {
  Plane p = Plane();
  p.SetTransform(RotationZ(M_PI / 2.0));
  Ray r = Ray(Point(2.0, 0.0, 0.0), Vector(-1.0, 0.0, 0.0));
  Intersections xs = p.Intersect(r);
  ASSERT_EQ(xs.Size(), 1);
  Intersection hit = xs.Hit().value();
  ASSERT_EQ(hit.T(), 2.0);
  ASSERT_EQ(hit.Object(), &p);
}

TEST(PlaneTest, NormalRotated) {
  Plane p = Plane();
  p.SetTransform(RotationZ(M_PI / 4.0));
  Tuple n1 = p.Normal(Point(0.0, 0.0, 0.0));
  ASSERT_EQ(n1, Vector(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0));
}
