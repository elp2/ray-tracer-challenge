#include "gtest/gtest.h"

#include <algorithm>
#include <math.h>

#include "primitives/transformation.h"
#include "shapes/sphere.h"
#include "scene/world.h"

class WorldTest : public ::testing::Test {
 protected:
  WorldTest() {};
  ~WorldTest() {};
};

TEST(WorldTest, EmptyWorld) {
  World w = World();
  ASSERT_EQ(w.objects().size(), 0);
  ASSERT_EQ(w.light(), PointLight());
}

TEST(WorldTest, IntersectWithRay) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = w.Intersect(r);
  ASSERT_EQ(xs.Size(), 4);
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 4.5);
  ASSERT_FLOAT_EQ(xs[2].T(), 5.5);
  ASSERT_FLOAT_EQ(xs[3].T(), 6);
}

TEST(WorldTest, ShadingIntersection) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  Sphere s = w.objects()[0];

  Intersections xs = s.Intersect(r);
  ASSERT_TRUE(xs.Hit().has_value());
  Intersection i = xs.Hit().value();

  PreparedComputation pc = PreparedComputation(i, r);
  Color c = w.ShadeHit(pc);
  ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionFromInside) {
  World w = DefaultWorld();
  w.set_light(PointLight(Point(0.0, 0.25, 0), Color(1.0, 1.0, 1.0)));

  Ray r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
  Sphere s = w.objects()[1];

  Intersections xs = s.Intersect(r);
  ASSERT_TRUE(xs.Hit().has_value());
  Intersection i = xs.Hit().value();

  PreparedComputation pc = PreparedComputation(i, r);
  Color c = w.ShadeHit(pc);
  ASSERT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldTest, ColorForMissedRay) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 1.0, 0.0));

  Color c = w.ColorAt(r);
  ASSERT_EQ(c, Color(0.0, 0.0, 0.0));
}

TEST(WorldTest, ColorForHitRay) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));

  Color c = w.ColorAt(r);
  ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorForIntersectionBehindRay) {
  World dw = DefaultWorld();
  Sphere s1 = dw.objects()[0];
  Material m1 = s1.material();
  m1.set_ambient(1.0);
  s1.set_material(m1);
  Sphere s2 = dw.objects()[1];
  Material m2 = s2.material();
  m2.set_ambient(1.0);
  s2.set_material(m2);

  World w = World();
  w.set_light(dw.light());
  w.add_object(s1);
  w.add_object(s2);

  Sphere outer = w.objects()[0];
  Sphere inner = w.objects()[1];
  Ray r = Ray(Point(0.0, 0.0, 0.75), Vector(0.0, 0.0, -1.0));
  Color c = w.ColorAt(r);
  ASSERT_EQ(inner.material().color(), c);
}

TEST(WorldTest, NothingColiniarWithPointAndLight) {
  World w = DefaultWorld();

  Tuple p = Point(0.0, 10.0, 0.0);
  ASSERT_FALSE(w.IsShadowed(p));
}

TEST(WorldTest, ObjectBetweenPointAndLight) {
  World w = DefaultWorld();

  Tuple p = Point(10.0, -10.0, 10.0);
  ASSERT_TRUE(w.IsShadowed(p));
}

TEST(WorldTest, NoShadowBeforeObject) {
  World w = DefaultWorld();

  Tuple p = Point(-20.0, 20.0, -20.0);
  ASSERT_FALSE(w.IsShadowed(p));
}

TEST(WorldTest, NoShadowBehindLight) {
  World w = DefaultWorld();

  Tuple p = Point(-2.0, 2.0, -2.0);
  ASSERT_FALSE(w.IsShadowed(p));
}
