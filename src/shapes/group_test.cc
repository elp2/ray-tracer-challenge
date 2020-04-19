#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/group.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include "shapes/sphere.h"

#include <math.h>
#include <vector>

class GroupTest : public ::testing::Test {
 protected:
  GroupTest() {};
  ~GroupTest() {};
};

TEST(GroupTest, ChildrenEmptyOnInit) {
  Group g = Group();
  ASSERT_EQ(g.size(), 0);
}

TEST(GroupTest, ShapesHaveNoDefaultParent) {
  auto s = new Sphere();
  ASSERT_EQ(s->parent(), nullptr);
}

TEST(GroupTest, AddsChild) {
  auto s = new Sphere();
  auto g = new Group();
  g->AddChild(s);
  ASSERT_EQ(g->size(), 1);
  auto children = g->children();
  EXPECT_EQ((*children)[0], s);
  EXPECT_EQ(s->parent(), g);
}

TEST(GroupTest, NoIntersectionsForEmptyGroup) {
  auto g = new Group();
  auto xs = g->Intersect(Ray(Point(0, 0, 0), Vector(1, 1, 1)));
  ASSERT_EQ(xs.Size(), 0);
}

TEST(GroupTest, IntersectRay) {
  auto g = new Group();
  auto s1 = new Sphere();
  auto s2 = new Sphere();
  s2->SetTransform(Translation(0, 0, -3));
  auto s3 = new Sphere();
  s3->SetTransform(Translation(5, 0, 0));
  g->AddChild(s1);
  g->AddChild(s2);
  g->AddChild(s3);

  Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto xs = g->ObjectIntersect(r);
  ASSERT_EQ(xs.Size(), 4);
  EXPECT_EQ(xs[0].Object(), s2);
  EXPECT_EQ(xs[1].Object(), s2);
  EXPECT_EQ(xs[2].Object(), s1);
  EXPECT_EQ(xs[3].Object(), s1);
}

TEST(GroupTest, IntersectTransformedGroup) {
  auto g = new Group();
  g->SetTransform(Scaling(2, 2, 2));
  auto s = new Sphere();
  s->SetTransform(Translation(5, 0, 0));
  g->AddChild(s);

  Ray r = Ray(Point(10, 0, -10), Vector(0, 0, 1));
  auto xs = g->Intersect(r);
  ASSERT_EQ(xs.Size(), 2);
}

TEST(GroupTest, ConvertPointFromWorldToObject) {
  auto g1 = new Group();
  g1->SetTransform(RotationY(M_PI / 2.0));
  auto g2 = new Group();
  g2->SetTransform(Scaling(2, 2, 2));
  g1->AddChild(g2);

  auto s = new Sphere();
  s->SetTransform(Translation(5, 0, 0));
  g2->AddChild(s);
  Tuple world_point = Point(-2, 0, -10);
  Tuple p = s->WorldPointToObject(world_point);
  ASSERT_EQ(Point(0, 0, -1), p);
}

TEST(GroupTest, ConvertNormalObjectToWorld) {
  auto g1 = new Group();
  g1->SetTransform(RotationY(M_PI / 2.0));
  auto g2 = new Group();
  g2->SetTransform(Scaling(1, 2, 3));
  g1->AddChild(g2);

  auto s = new Sphere();
  s->SetTransform(Translation(5, 0, 0));
  g2->AddChild(s);
  Tuple object_normal = Vector(sqrt(3.0) / 3, sqrt(3.0) / 3, sqrt(3.0) / 3);
  Tuple world_normal = s->ObjectNormalToWorld(object_normal);

  // BOOK DIFF: Vector(0.2857, 0.4286, -0.8571)
  ASSERT_EQ(world_normal, Vector(0.285714, 0.428571, -0.8571431));
}

TEST(GroupTest, ChildNormal) {
  auto g1 = new Group();
  g1->SetTransform(RotationY(M_PI / 2.0));
  auto g2 = new Group();
  g2->SetTransform(Scaling(1, 2, 3));
  g1->AddChild(g2);

  auto s = new Sphere();
  s->SetTransform(Translation(5, 0, 0));
  g2->AddChild(s);
  Tuple normal_point = Point(1.7321, 1.1547, -5.5774);
  // BOOK DIFF: Vector(0.2857, 0.4286, -0.8571)

  ASSERT_EQ(s->Normal(normal_point, Intersection(1, &s)), Vector(0.285704, 0.428543, -0.857161));
}

TEST(GroupTest, EmptyBounds) {
  auto g = new Group();
  EXPECT_EQ(g->UnitBounds().maximum(), Point(0, 0, 0));
  EXPECT_EQ(g->UnitBounds().minimum(), Point(0, 0, 0));
}

TEST(GroupTest, UntransformedSphere) {
  auto g = new Group();
  auto s = new Sphere();
  g->AddChild(s);
  EXPECT_EQ(g->UnitBounds().maximum(), Point(1, 1, 1));
  EXPECT_EQ(g->UnitBounds().minimum(), Point(-1, -1, -1));
}

TEST(GroupTest, TransformedSphere) {
  auto g = new Group();
  auto s = new Sphere();
  s->SetTransform(Translation(2, 0, 0) * Scaling(2, 2, 2));
  g->AddChild(s);

  EXPECT_EQ(g->UnitBounds().maximum(), Point(4, 2, 2));
  EXPECT_EQ(g->UnitBounds().minimum(), Point(0, -2, -2));
}

TEST(GroupTest, TransformedGroupCeption) {
  auto g1 = new Group();
  auto s = new Sphere();
  s->SetTransform(Translation(2, 0, 0) * Scaling(2, 2, 2));
  g1->AddChild(s);
  g1->SetTransform(RotationY(M_PI));
  auto g2 = new Group();
  g2->AddChild(g1);

  EXPECT_EQ(g2->UnitBounds().maximum(), Point(0, 2, 2));
  EXPECT_EQ(g2->UnitBounds().minimum(), Point(-4, -2, -2));
}

TEST(GroupTest, TransformedSphereIntersections) {
  auto g = new Group();
  auto s = new Sphere();
  s->SetTransform(Translation(2, 0, 0) * Scaling(2, 2, 2));
  g->AddChild(s);

  EXPECT_EQ(g->Intersect(Ray(Point(-0.1, 0, 0), Vector(0, 1, 0))).Size(), 0);
  EXPECT_EQ(g->Intersect(Ray(Point(0.1, 0, 0), Vector(0, 1, 0))).Size(), 2);
  EXPECT_EQ(g->Intersect(Ray(Point(3.9, 0, 0), Vector(0, 1, 0))).Size(), 2);
  EXPECT_EQ(g->Intersect(Ray(Point(4.1, 0, 0), Vector(0, 1, 0))).Size(), 0);
}
