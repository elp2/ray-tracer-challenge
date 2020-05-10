#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/cylinder.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class CylinderTest : public ::testing::Test {
 protected:
  CylinderTest() {};
  ~CylinderTest() {};
};

TEST(CylinderTest, RayMissesCylinder) {
  std::vector<Tuple> origins = {
    Point(1, 0, 0),
    Point(0, 0, 0),
    Point(0, 0, -5),
  };
  std::vector<Tuple> directions = {
    Vector(0, 1, 0),
    Vector(0, 1, 0),
    Vector(1, 1, 1),
  };
  Cylinder c = Cylinder();
  for (int i = 0; i < 3; ++i) {
    Ray r = Ray(origins[i], directions[i]);
    Intersections xs = c.ObjectIntersect(r);
    ASSERT_EQ(xs.Size(), 0);
  }
}

TEST(CylinderTest, RayHitsCylinder) {
  std::vector<Tuple> origins = {
    Point(1, 0, -5),
    Point(0, 0, -5),
    Point(0.5, 0, -5),
  };
  std::vector<Tuple> directions = {
    Vector(0, 0, 1),
    Vector(0, 0, 1),
    Vector(0.1, 1, 1),
  };
  std::vector<float> t0s = { 5, 4, 6.8079939 };
  std::vector<float> t1s = { 5, 6, 7.0887103 };
  // BOOK DIFF: 6.80798, 7.08872
  Cylinder c = Cylinder();
  for (int i = 0; i < 3; ++i) {
    Ray r = Ray(origins[i], directions[i].Normalized());
    Intersections xs = c.ObjectIntersect(r);
    ASSERT_EQ(xs.Size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), t0s[i]);
    EXPECT_FLOAT_EQ(xs[1].T(), t1s[i]);
  }
}

TEST(CylinderTest, Normals) {
  std::vector<Tuple> surface_points = {
    Point(1, 0, 0),
    Point(0, 5, -1),
    Point(0, -2, 1),
    Point(-1, 1, 0),
  };
  std::vector<Tuple> normals = {
    Vector(1, 0, 0),
    Vector(0, 0, -1),
    Vector(0, 0, 1),
    Vector(-1, 0, 0),
  };
  Cylinder c = Cylinder();
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(c.Normal(surface_points[i], Intersection(1, &c)), normals[i]);
  }
}

TEST(CylinderTest, DefaultMaxMin) {
  auto c = Cylinder();
  ASSERT_EQ(c.maximum(), INFINITY);
  ASSERT_EQ(c.minimum(), -INFINITY);
}

TEST(CylinderTest, IntersectingConstrainedCylinder) {
  std::vector<Tuple> points = {
      Point(0, 1.5, 0),
      Point(0, 3, -5),
      Point(0, 0, -5),
      Point(0, 2, -5),
      Point(0, 1, -5),
      Point(0, 1.5, -2),
  };
  std::vector<Tuple> directions = {
      Vector(0.1, 1, 0),
      Vector(0, 0, 1),
      Vector(0, 0, 1),
      Vector(0, 0, 1),
      Vector(0, 0, 1),
      Vector(0, 0, 1),
  };
  std::vector<int> counts = { 0, 0, 0, 0, 0, 2 };

  auto c = Cylinder(2, 1, false);
  for (int i = 0; i < 6; ++i) {
    Ray r = Ray(points[i], directions[i].Normalized());
    Intersections xs = c.Intersect(r);
    ASSERT_EQ(xs.Size(), counts[i]);
  }
}

TEST(CylinderTest, OpenByDefault) {
  auto c = Cylinder();
  ASSERT_FALSE(c.closed());
}

TEST(CylinderTest, IntersectingCappedCylinder) {
  std::vector<Tuple> points = {
      Point(0, 4, -2),
      Point(0, -1, -2),
      Point(0, 3, 0),
      Point(0, 3, -2),
      Point(0, 0, -2),
  };
  std::vector<Tuple> directions = {
      Vector(0, -1, 1),
      Vector(0, 1, 1),
      Vector(0, -1, 0),
      Vector(0, -1, 2),
      Vector(0, 1, 2),
  };
  std::vector<int> counts = { 2, 2, 2, 2, 2 };

  auto c = Cylinder(2, 1, true);
  for (std::vector<Tuple>::size_type i = 0; i < points.size(); ++i) {
    Ray r = Ray(points[i], directions[i].Normalized());
    Intersections xs = c.ObjectIntersect(r);
    EXPECT_EQ(xs.Size(), counts[i]);
  }
}

TEST(CylinderTest, CapNormals) {
  std::vector<Tuple> points = {
      Point(0, 1, 0),
      Point(0.5, 1, 0),
      Point(0, 1, 0.5),
      Point(0, 2, 0),
      Point(0.5, 2, 0),
      Point(0, 2, 0.5),
  };
  std::vector<Tuple> normals = {
      Vector(0, -1 ,0),
      Vector(0, -1 ,0),
      Vector(0, -1 ,0),
      Vector(0, 1, 0),
      Vector(0, 1, 0),
      Vector(0, 1, 0),
  };

  ASSERT_EQ(points.size(), normals.size());
  Cylinder c = Cylinder(2, 1, true);
  for (std::vector<Tuple>::size_type i = 0; i < points.size(); ++i) {
    EXPECT_EQ(c.ObjectNormal(points[i], Intersection(1, &c)), normals[i]);
  }
}
