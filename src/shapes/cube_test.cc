#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/cube.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class CubeTest : public ::testing::Test {
 protected:
  CubeTest() {};
  ~CubeTest() {};
};

TEST(CubeTest, RayIntersectsCube) {
  std::vector<Tuple> origins = {
    Point(5, 0.5, 0),
    Point(-5, 0.5, 0),
    Point(0.5, 5, 0),
    Point(0.5, -5, 0),
    Point(0.5, 0, 5),
    Point(0.5, 0, -5),
    Point(0, 0.5, 0),
  };
  std::vector<Tuple> directions = {
    Vector(-1, 0, 0),
    Vector(1, 0, 0),
    Vector(0, -1, 0),
    Vector(0, 1, 0),
    Vector(0, 0, -1),
    Vector(0, 0, 1),
    Vector(0, 0, 1),
  };
  std::vector<float> t1s = { 4, 4, 4, 4, 4, 4, -1};
  std::vector<float> t2s = {6, 6, 6, 6, 6, 6, 1};
  Cube c = Cube();
  for (int i = 0; i < 7; ++i) {
    Ray r = Ray(origins[i], directions[i]);
    Intersections xs = c.Intersect(r);
    ASSERT_EQ(xs.Size(), 2);
    ASSERT_FLOAT_EQ(xs[0].T(), t1s[i]);
    ASSERT_FLOAT_EQ(xs[1].T(), t2s[i]);
  }
}

TEST(CubeTest, RayMissesCube) {
  std::vector<Tuple> origins = {
    Point(-2, 0, 0),
    Point(0, -2, 0),
    Point(0, 0, -2),
    Point(2, 0, 2),
    Point(0, 2, 2),
    Point(2, 2, 0),
  };
  std::vector<Tuple> directions = {
    Vector(0.2673, 0.5345, 0.8018),
    Vector(0.8018, 0.2673, 0.5345),
    Vector(0.5345, 0.8018, 0.2673),
    Vector(0, 0, -1),
    Vector(0, -1, 0),
    Vector(-1, 0, 0),
  };
  Cube c = Cube();
  for (int i = 0; i < 6; ++i) {
    Ray r = Ray(origins[i], directions[i]);
    Intersections xs = c.Intersect(r);
    ASSERT_FALSE(xs.Hit().has_value());
  }
}

TEST(CubeTest, Normals) {
  std::vector<Tuple> surface_points = {
    Point(1, 0.5, -0.8),
    Point(-1, -0.2, 0.9),
    Point(-0.4, 1, -0.1),
    Point(0.3, -1, -0.7),
    Point(-0.6, 0.3, 1),
    Point(0.4, 0.4, -1),
    Point(1, 1, 1),
    Point(-1, -1, -1),
  };
  std::vector<Tuple> normals = {
    Vector(1, 0, 0),
    Vector(-1, 0, 0),
    Vector(0, 1, 0),
    Vector(0, -1, 0),
    Vector(0, 0, 1),
    Vector(0, 0, -1),
    Vector(1, 0, 0),
    Vector(-1, 0, 0),
  };
  Cube c = Cube();
  for (int i = 0; i < 8; ++i) {
    ASSERT_EQ(c.Normal(surface_points[i]), normals[i]);
  }
}
