#include "gtest/gtest.h"

#include "primitives/math.h"
#include "primitives/ray.h"
#include "scene/prepared_computation.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <math.h>

class PreparedComputationTest : public ::testing::Test {
 protected:
  PreparedComputationTest() {};
  ~PreparedComputationTest() {};
};

TEST(PreparedComputationTest, Precompute) {
  Sphere s = Sphere();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = s.Intersect(r);
  Intersection i = xs[0];
  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_FLOAT_EQ(pc.t(), i.T());
  ASSERT_EQ(pc.object(), i.Object());
  ASSERT_EQ(pc.point(), Point(0.0, 0.0, -1.0));
  ASSERT_EQ(pc.eye_vector(), Vector(0.0, 0.0, -1.0));
  ASSERT_EQ(pc.normal_vector(), Vector(0.0, 0.0, -1.0));
}

TEST(PreparedComputationTest, Outside) {
  Sphere s = Sphere();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));

  Intersections xs = s.Intersect(r);
  std::optional<Intersection> hit = xs.Hit();
  ASSERT_TRUE(hit.has_value());
  Intersection i = hit.value();

  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_FALSE(pc.inside());
}

TEST(PreparedComputationTest, Inside) {
  Sphere s = Sphere();
  Ray r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

  Intersections xs = s.Intersect(r);
  std::optional<Intersection> hit = xs.Hit();
  ASSERT_TRUE(hit.has_value());
  Intersection i = hit.value();

  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_EQ(pc.point(), Point(0.0, 0.0, 1.0));
  ASSERT_EQ(pc.eye_vector(), Vector(0.0, 0.0, -1.0));
  ASSERT_TRUE(pc.inside());
  // Inverted because inside.
  ASSERT_EQ(pc.normal_vector(), Vector(0.0, 0.0, -1.0));
}

TEST(PreparedComputationTest, HitOffsetsPoint) {
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  Sphere s = Sphere();
  Intersection i = s.Intersect(r).Hit().value();
  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_LT(pc.over_point().z(), -EPSILON / 2.0);
  ASSERT_GT(pc.point().z(), pc.over_point().z());
}

TEST(PreparedComputationTest, PreparesReflectionVector) {
  Ray r = Ray(Point(0, 1, -1), Vector(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
  Plane s = Plane();
  Intersection i = s.Intersect(r).Hit().value();
  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_EQ(Vector(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0), pc.reflect_vector());
}
