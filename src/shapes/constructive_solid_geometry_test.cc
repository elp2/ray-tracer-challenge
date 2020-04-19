#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include "shapes/constructive_solid_geometry.h"
#include "shapes/cube.h"
#include "shapes/sphere.h"

#include <math.h>
#include <vector>

class ConstructiveSolidGeometryTest : public ::testing::Test {
 protected:
  ConstructiveSolidGeometryTest() {};
  ~ConstructiveSolidGeometryTest() {};
};

TEST(ConstructiveSolidGeometryTest, Creation) {
  auto sphere = new Sphere();
  auto cube = new Cube();
  auto csg = ConstructiveSolidGeometry(sphere, cube,
      new UnionIntersectionStrategy());
  EXPECT_EQ(csg.left(), sphere);
  EXPECT_EQ(csg.right(), cube);
  EXPECT_EQ(sphere->parent(), &csg);
  EXPECT_EQ(cube->parent(), &csg);
}

TEST(ConstructiveSolidGeometryTest, UnionIntersectionStrategy) {
  UnionIntersectionStrategy *strategy = new UnionIntersectionStrategy();

  EXPECT_FALSE(strategy->IntersectionAllowed(true, true, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(true, true, false));
  EXPECT_FALSE(strategy->IntersectionAllowed(true, false, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(true, false, false));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, true, true));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, true, false));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, false, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, false, false));
}

TEST(ConstructiveSolidGeometryTest, IntersectIntersectionStrategy) {
  IntersectIntersectionStrategy *strategy = new IntersectIntersectionStrategy();

  EXPECT_TRUE(strategy->IntersectionAllowed(true, true, true));
  EXPECT_FALSE(strategy->IntersectionAllowed(true, true, false));
  EXPECT_TRUE(strategy->IntersectionAllowed(true, false, true));
  EXPECT_FALSE(strategy->IntersectionAllowed(true, false, false));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, true, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, true, false));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, false, true));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, false, false));
}

TEST(ConstructiveSolidGeometryTest, DifferenceIntersectionStrategy) {
  DifferenceIntersectionStrategy *strategy = new DifferenceIntersectionStrategy();

  EXPECT_FALSE(strategy->IntersectionAllowed(true, true, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(true, true, false));
  EXPECT_FALSE(strategy->IntersectionAllowed(true, false, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(true, false, false));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, true, true));
  EXPECT_TRUE(strategy->IntersectionAllowed(false, true, false));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, false, true));
  EXPECT_FALSE(strategy->IntersectionAllowed(false, false, false));
}

TEST(ConstructiveSolidGeometryTest, FiltersIntersections) {
  auto sphere = new Sphere();
  auto cube = new Cube();

  Intersections xs = Intersections(std::vector<Intersection> {
    Intersection(1, sphere),
    Intersection(2, cube),
    Intersection(3, sphere),
    Intersection(4, cube),
  });

  auto uis = ConstructiveSolidGeometry(sphere, cube,
      new UnionIntersectionStrategy());
  auto filtered = uis.FilterIntersections(xs);
  ASSERT_EQ(filtered.Size(), 2);
  EXPECT_EQ(filtered[0].T(), 1);
  EXPECT_EQ(filtered[1].T(), 4);

  auto iis = ConstructiveSolidGeometry(sphere, cube,
      new IntersectIntersectionStrategy());
  filtered = iis.FilterIntersections(xs);
  ASSERT_EQ(filtered.Size(), 2);
  EXPECT_EQ(filtered[0].T(), 2);
  EXPECT_EQ(filtered[1].T(), 3);

  auto dis = ConstructiveSolidGeometry(sphere, cube,
      new DifferenceIntersectionStrategy());
  filtered = dis.FilterIntersections(xs);
  ASSERT_EQ(filtered.Size(), 2);
  EXPECT_EQ(filtered[0].T(), 1);
  EXPECT_EQ(filtered[1].T(), 2);
}

TEST(ConstructiveSolidGeometryTest, RayMisses) {
  auto sphere = new Sphere();
  auto cube = new Cube();
  auto uis = ConstructiveSolidGeometry(sphere, cube,
      new UnionIntersectionStrategy());

  Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
  Intersections xs = uis.Intersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(ConstructiveSolidGeometryTest, RayHits) {
  auto s1 = new Sphere();
  auto s2 = new Sphere();
  s2->SetTransform(Translation(0, 0, 0.5));
  auto uis = ConstructiveSolidGeometry(s1, s2,
      new UnionIntersectionStrategy());

  Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = uis.Intersect(r);
  ASSERT_EQ(xs.Size(), 2);
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_EQ(xs[0].Object(), s1);
  ASSERT_FLOAT_EQ(xs[1].T(), 6.5);
  ASSERT_EQ(xs[1].Object(), s2);
}
