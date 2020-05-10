#include "gtest/gtest.h"

#include "primitives/math.h"
#include "primitives/ray.h"
#include "primitives/transformation.h"
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
  PreparedComputation pc = PreparedComputation(i, r, xs);
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

  PreparedComputation pc = PreparedComputation(i, r, xs);
  ASSERT_FALSE(pc.inside());
}

TEST(PreparedComputationTest, Inside) {
  Sphere s = Sphere();
  Ray r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

  Intersections xs = s.Intersect(r);
  std::optional<Intersection> hit = xs.Hit();
  ASSERT_TRUE(hit.has_value());
  Intersection i = hit.value();

  PreparedComputation pc = PreparedComputation(i, r, xs);
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
  Intersections xs = Intersections(std::vector<Intersection> { i });
  PreparedComputation pc = PreparedComputation(i, r, xs);
  ASSERT_LT(pc.over_point().z(), -EPSILON / 2.0);
  ASSERT_GT(pc.point().z(), pc.over_point().z());
}

TEST(PreparedComputationTest, UnderPoint) {
  Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s = Sphere();
  s.SetTransform(Translation(0, 0, 1));
  Intersection i = s.Intersect(r).Hit().value();
  Intersections xs = Intersections(std::vector<Intersection> { i });
  PreparedComputation pc = PreparedComputation(i, r, xs);
  ASSERT_GT(pc.under_point().z(), EPSILON / 2.0);
  ASSERT_LT(pc.point().z(), pc.under_point().z());
}

TEST(PreparedComputationTest, PreparesReflectionVector) {
  Ray r = Ray(Point(0, 1, -1), Vector(0, -sqrt(2) / 2.0, sqrt(2) / 2.0));
  Plane s = Plane();
  Intersection i = s.Intersect(r).Hit().value();
  Intersections xs = Intersections(std::vector<Intersection> { i });
  PreparedComputation pc = PreparedComputation(i, r, xs);
  ASSERT_EQ(Vector(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0), pc.reflect_vector());
}

TEST(PreparedComputationTest, N1N2) {
  auto a = GlassySphere();
  Material ma = Material();
  a->SetTransform(Scaling(2, 2, 2));
  ma.set_refractive_index(1.5);
  a->set_material(ma);

  auto b = GlassySphere();
  Material mb = Material();
  b->SetTransform(Translation(0, 0, -0.25));
  mb.set_refractive_index(2.0);
  b->set_material(mb);

  auto c = GlassySphere();
  Material mc = Material();
  c->SetTransform(Translation(0, 0, 0.25));
  mc.set_refractive_index(2.5);
  c->set_material(mc);

  Ray r = Ray(Point(0, 0, -4), Vector(0, 0, 1));
  auto xs = Intersections(std::vector<Intersection> {
    Intersection(2, a),
    Intersection(2.75, b),
    Intersection(3.25, c),
    Intersection(4.75, b),
    Intersection(5.25, c),
    Intersection(6, a),
  });
  auto n1s = std::vector<float> { 1.0, 1.5, 2.0, 2.5, 2.5, 1.5 };
  auto n2s = std::vector<float> { 1.5, 2.0, 2.5, 2.5, 1.5, 1.0 };

  for (std::vector<Tuple>::size_type i = 0; i < xs.Size(); ++i) {
    PreparedComputation pc = PreparedComputation(xs[i], r, xs);
    ASSERT_FLOAT_EQ(pc.n1(), n1s[i]);
    ASSERT_FLOAT_EQ(pc.n2(), n2s[i]);
  }
}
