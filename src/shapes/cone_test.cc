#include "gtest/gtest.h"

#include "primitives/intersections.h"
#include "primitives/ray.h"
#include "shapes/cone.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class ConeTest : public ::testing::Test {
 protected:
  ConeTest() {};
  ~ConeTest() {};
};

TEST(ConeTest, RayHitsCone) {
  std::vector<Tuple> origins = {
    Point(0, 0, -5),
    Point(0, 0, -5),
    Point(1, 1, -5),
  };
  std::vector<Tuple> directions = {
    Vector(0, 0, 1),
    Vector(1, 1, 1),
    Vector(-0.5, -1, 1),
  };
  // BOOK DIFF: 8.66025, 4.550056
  std::vector<float> t0s = { 5, 8.6602545, 4.550056 };
  std::vector<float> t1s = { 5, 8.6602545, 49.44994 };

  Cone c = Cone();
  for (int i = 0; i < t0s.size(); ++i) {
    Ray r = Ray(origins[i], directions[i].Normalized());
    Intersections xs = c.ObjectIntersect(r);
    ASSERT_EQ(xs.Size(), 2);
    EXPECT_FLOAT_EQ(xs[0].T(), t0s[i]);
    EXPECT_FLOAT_EQ(xs[1].T(), t1s[i]);
  }
}

TEST(ConeTest, RayParallelToOneHalf) {
  Cone c = Cone();
  Ray r = Ray(Point(0, 0, -1), Vector(0, 1, 1).Normalized());
  Intersections xs = c.ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 1);
  // BOOK DIFF: 0.35355
  EXPECT_FLOAT_EQ(xs[0].T(), 0.3535533);
}

TEST(ConeTest, IntersectingCappedCone) {
  std::vector<Tuple> points = {
      Point(0, 0, -5),
      Point(0, 0, -0.25),
      Point(0, 0, -0.25),
  };
  std::vector<Tuple> directions = {
      Vector(0, 1, 0),
      Vector(0, 1, 1),
      Vector(0, 1, 0),
  };
  std::vector<int> counts = { 0, 2, 4 };

  auto c = Cone(0.5, -0.5, true);
  for (int i = 0; i < points.size(); ++i) {
    Ray r = Ray(points[i], directions[i].Normalized());
    Intersections xs = c.ObjectIntersect(r);
    EXPECT_EQ(xs.Size(), counts[i]);
  }
}

TEST(ConeTest, Normals) {
  std::vector<Tuple> surface_points = {
    Point(0, 0, 0),
    Point(1, 1, 1),
    Point(-1, -1, 0),
  };
  std::vector<Tuple> normals = {
    Vector(0, 0, 0),
    Vector(1, -sqrt(2.0), 1),
    Vector(-1, 1, 0),
  };
  Cone c = Cone();
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(c.ObjectNormal(surface_points[i]), normals[i]);
  }
}

TEST(ConeTest, DefaultMaxMin) {
  auto c = Cone();
  ASSERT_EQ(c.maximum(), INFINITY);
  ASSERT_EQ(c.minimum(), -INFINITY);
}
