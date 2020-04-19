#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/triangle.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class TriangleTest : public ::testing::Test {
 protected:
  TriangleTest() {};
  ~TriangleTest() {};
};

TEST(TriangleTest, ConstructingTriangle) {
  Tuple p1 = Point(0, 1, 0);
  Tuple p2 = Point(-1, 0, 0);
  Tuple p3 = Point(1, 0, 0);

  Triangle t = Triangle(p1, p2, p3);
  EXPECT_EQ(t.p1(), p1);
  EXPECT_EQ(t.p2(), p2);
  EXPECT_EQ(t.p3(), p3);

  EXPECT_EQ(t.e1(), Vector(-1, -1, 0));
  EXPECT_EQ(t.e2(), Vector(1, -1, 0));
  EXPECT_EQ(t.precalculated_normal(), Vector(0, 0, -1));
}

TEST(TriangleTest, ConstructingTriangleX) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Tuple n1 = t.ObjectNormal(Point(0, 0.5, 0));
  Tuple n2 = t.ObjectNormal(Point(-0.5, 0.75, 0));
  Tuple n3 = t.ObjectNormal(Point(0.5, 0.25, 0));

  EXPECT_EQ(t.precalculated_normal(), n1);
  EXPECT_EQ(t.precalculated_normal(), n2);
  EXPECT_EQ(t.precalculated_normal(), n3);
}

TEST(TriangleTest, MissedParallelRay) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r = Ray(Point(0, -1, -2), Vector(0, 1, 0));
  Intersections xs = t.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(TriangleTest, RayPassesP1P3Edge) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r = Ray(Point(1, 1, -2), Vector(0, 0, 1));
  auto xs = t.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(TriangleTest, RayPassesP1P2Edge) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r = Ray(Point(-1, 1, -2), Vector(0, 0, 1));
  auto xs = t.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(TriangleTest, RayPassesP2P3Edge) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r = Ray(Point(0, -1, -2), Vector(0, 0, 1));
  auto xs = t.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(TriangleTest, RayStrikesTriangle) {
  Triangle t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r = Ray(Point(0, 0.5, -2), Vector(0, 0, 1));
  auto xs = t.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 1);
  EXPECT_EQ(xs.Hit().value().T(), 2);
}
