#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/smooth_triangle.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "scene/prepared_computation.h"

#include <math.h>
#include <vector>

class SmoothTriangleTest : public ::testing::Test {
 protected:
  SmoothTriangleTest() {};
  ~SmoothTriangleTest() {};

  Tuple p1_ = Point(0, 1, 0);
  Tuple p2_ = Point(-1, 0, 0);
  Tuple p3_ = Point(1, 0, 0);

  Tuple n1_ = Vector(0, 1, 0);
  Tuple n2_ = Vector(-1, 0, 0);
  Tuple n3_ = Vector(1, 0, 0);

  SmoothTriangle tri_ = SmoothTriangle(p1_, p2_, p3_, n1_, n2_, n3_);
};

TEST_F(SmoothTriangleTest, ConstructingSmoothTriangle) {
  EXPECT_EQ(tri_.p1(), p1_);
  EXPECT_EQ(tri_.p2(), p2_);
  EXPECT_EQ(tri_.p3(), p3_);

  EXPECT_EQ(tri_.n1(), n1_);
  EXPECT_EQ(tri_.n2(), n2_);
  EXPECT_EQ(tri_.n3(), n3_);
}

TEST_F(SmoothTriangleTest, SetsUVOnIntersectionSetsUVOnIntersection) {
  Ray r = Ray(Point(-0.2, 0.3, -2), Vector(0, 0, 1));
  Intersections xs = tri_.ObjectIntersect(r);
  ASSERT_TRUE(xs.Hit().has_value());
  EXPECT_FLOAT_EQ(xs.Hit().value().u(), 0.45);
  EXPECT_FLOAT_EQ(xs.Hit().value().v(), 0.25);
}

TEST_F(SmoothTriangleTest, UsesUVToInterpolateNormal) {
  Intersection i = Intersection(1, &tri_, 0.45, 0.25);
  Tuple n = tri_.ObjectNormal(Point(0, 0, 0), i).Normalized();
  ASSERT_EQ(Vector(-0.5547, 0.83205, 0), n);
}

TEST_F(SmoothTriangleTest, PreparedComputation) {
  Intersection i = Intersection(1, &tri_, 0.45, 0.25);
  Ray r = Ray(Point(-0.2, 0.3, -2), Vector(0, 0, 1));
  Intersections xs = Intersections(std::vector<Intersection> { i });
  PreparedComputation pc = PreparedComputation(i, r, xs);
  EXPECT_EQ(pc.normal_vector(), Vector(-0.5547, 0.83205, 0));
}
