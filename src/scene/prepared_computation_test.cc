#include "gtest/gtest.h"

#include "scene/prepared_computation.h"
#include "shapes/sphere.h"

class PreparedComputationTest : public ::testing::Test {
 protected:
  PreparedComputationTest() {};
  ~PreparedComputationTest() {};
};

TEST(PreparedComputationTest, Precompute) {
  Sphere s = Sphere();
  Ray r = Ray(TupleFromPoint(0.0, 0.0, -5.0), TupleFromVector(0.0, 0.0, 1.0));
  Intersections xs = s.Intersect(r);
  Intersection i = xs[0];
  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_FLOAT_EQ(pc.t(), i.T());
  ASSERT_EQ(pc.object(), i.Object());
  ASSERT_EQ(pc.point(), TupleFromPoint(0.0, 0.0, -1.0));
  ASSERT_EQ(pc.eye_vector(), TupleFromVector(0.0, 0.0, -1.0));
  ASSERT_EQ(pc.normal_vector(), TupleFromVector(0.0, 0.0, -1.0));
}

TEST(PreparedComputationTest, Outside) {
  Sphere s = Sphere();
  Ray r = Ray(TupleFromPoint(0.0, 0.0, -5.0), TupleFromVector(0.0, 0.0, 1.0));

  Intersections xs = s.Intersect(r);
  std::optional<Intersection> hit = xs.Hit();
  ASSERT_TRUE(hit.has_value());
  Intersection i = hit.value();

  PreparedComputation pc = PreparedComputation(i, r);
  ASSERT_FALSE(pc.inside());
}

TEST(PreparedComputationTest, Inside) {
  Sphere s = Sphere();
  Ray r = Ray(TupleFromPoint(0.0, 0.0, 0.0), TupleFromVector(0.0, 0.0, 1.0));

  Intersections xs = s.Intersect(r);
  std::optional<Intersection> hit = xs.Hit();
  ASSERT_TRUE(hit.has_value());
  Intersection i = hit.value();

  PreparedComputation pc = PreparedComputation(i, r);
  pc.point().Debug();
  ASSERT_EQ(pc.point(), TupleFromPoint(0.0, 0.0, 1.0));
  ASSERT_EQ(pc.eye_vector(), TupleFromVector(0.0, 0.0, -1.0));
  ASSERT_TRUE(pc.inside());
  // Inverted because inside.
  ASSERT_EQ(pc.normal_vector(), TupleFromVector(0.0, 0.0, -1.0));
}
