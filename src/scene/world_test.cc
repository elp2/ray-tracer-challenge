#include "gtest/gtest.h"

#include <algorithm>
#include <math.h>

#include "lights/point_light.h"
#include "primitives/intersections.h"
#include "primitives/transformation.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "scene/world.h"


class PatternMock : public Pattern {
 public:
  const Color PatternColorAt(const Tuple &object_point) const {
    return Color(object_point.x(), object_point.y(), object_point.z());
  }
};

class WorldTest : public ::testing::Test {
 protected:
  WorldTest() {};
  ~WorldTest() {};
};

TEST(WorldTest, EmptyWorld) {
  World w = World();
  ASSERT_EQ(w.objects().size(), 0);
  // TODO: Adjust == to work with pointers.
  // ASSERT_EQ(w.light(), new PointLight());
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
  auto s = w.objects()[0];

  Intersections xs = s->Intersect(r);
  ASSERT_TRUE(xs.Hit().has_value());
  Intersection i = xs.Hit().value();

  PreparedComputation pc = PreparedComputation(i, r, xs);
  Color c = w.ShadeHit(pc, 0);
  ASSERT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionFromInside) {
  World w = DefaultWorld();
  w.set_light(new PointLight(Point(0.0, 0.25, 0), Color(1.0, 1.0, 1.0)));

  Ray r = Ray(Point(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));
  auto s = w.objects()[1];

  Intersections xs = s->Intersect(r);
  ASSERT_TRUE(xs.Hit().has_value());
  Intersection i = xs.Hit().value();

  PreparedComputation pc = PreparedComputation(i, r, xs);
  Color c = w.ShadeHit(pc, 0);
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
  auto s1 = dw.objects()[0];
  Material m1 = s1->material();
  m1.set_ambient(1.0);
  s1->set_material(m1);
  auto s2 = dw.objects()[1];
  Material m2 = s2->material();
  m2.set_ambient(1.0);
  s2->set_material(m2);

  World w = World();
  w.set_light(dw.light());
  w.add_object(s1);
  w.add_object(s2);

  auto inner = w.objects()[1];
  Ray r = Ray(Point(0.0, 0.0, 0.75), Vector(0.0, 0.0, -1.0));
  Color c = w.ColorAt(r);
  ASSERT_EQ(inner->material().color(), c);
}

TEST(WorldTest, NothingColiniarWithPointAndLight) {
  World w = DefaultWorld();

  Tuple p = Point(0.0, 10.0, 0.0);
  ASSERT_FALSE(w.LightShadowed(p, w.light()->LightletsForPoint(p)[0]->position()));
}

TEST(WorldTest, ObjectBetweenPointAndLight) {
  World w = DefaultWorld();

  Tuple p = Point(10.0, -10.0, 10.0);
  ASSERT_TRUE(w.LightShadowed(p, w.light()->LightletsForPoint(p)[0]->position()));
}

TEST(WorldTest, NoShadowBeforeObject) {
  World w = DefaultWorld();

  Tuple p = Point(-20.0, 20.0, -20.0);
  ASSERT_FALSE(w.LightShadowed(p, w.light()->LightletsForPoint(p)[0]->position()));
}

TEST(WorldTest, NoShadowBehindLight) {
  World w = DefaultWorld();

  Tuple p = Point(-2.0, 2.0, -2.0);
  ASSERT_FALSE(w.LightShadowed(p, w.light()->LightletsForPoint(p)[0]->position()));
}

TEST(WorldTest, ShadeHitOnShadowedLocation) {
  World w = World();
  w.set_light(new PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0)));
  auto s1 = new Sphere();
  w.add_object(s1);
  auto s2 = new Sphere();
  s2->SetTransform(Translation(0.0, 0.0, 10.0));
  w.add_object(s2);

  Ray r = Ray(Point(0.0, 0.0, 5.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = w.Intersect(r);
  PreparedComputation pc = PreparedComputation(xs.Hit().value(), r, xs);

  Color c = w.ShadeHit(pc, 0);
  ASSERT_EQ(Color(0.1, 0.1, 0.1), c);
}

TEST(WorldTest, NonReflectiveMaterialReflectsBlack) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  Shape *s = w.objects()[1];
  Material m = s->material();
  m.set_ambient(1.0);

  Intersections xs = w.Intersect(r);
  PreparedComputation pc = PreparedComputation(xs.Hit().value(), r, xs);
  ASSERT_EQ(w.ReflectedColor(pc, 0), Color(0, 0, 0));
}

TEST(WorldTest, ReflectiveMaterialColor) {
  World w = DefaultWorld();
  auto p = new Plane();
  p->SetTransform(Translation(0, -1, 0));
  Material m = Material();
  m.set_reflective(0.5);
  p->set_material(m);
  w.add_object(p);

  Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
  Intersections xs = w.Intersect(r);
  PreparedComputation pc = PreparedComputation(xs.Hit().value(), r, xs);
  ASSERT_EQ(w.ReflectedColor(pc, 0), Color(0.190332, 0.237915, 0.142749));
}

TEST(WorldTest, ReflectShadeHit) {
  World w = DefaultWorld();
  auto p = new Plane();
  p->SetTransform(Translation(0, -1, 0));
  Material m = Material();
  m.set_reflective(0.5);
  p->set_material(m);
  w.add_object(p);

  Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
  Intersections xs = w.Intersect(r);
  PreparedComputation pc = PreparedComputation(xs.Hit().value(), r, xs);
  ASSERT_EQ(w.ShadeHit(pc, 0), Color(0.876758, 0.924341, 0.829175));
}

TEST(WorldTest, ReflectiveSurfaces) {
  World w = World();
  w.set_light(new PointLight(Point(0, 0, 0), Color(1, 1, 1)));
  auto lower = new Plane();
  auto reflective = Material();
  reflective.set_reflective(1.0);
  lower->set_material(reflective);
  lower->SetTransform(Translation(0, -1, 0));
  w.add_object(lower);
  auto upper = new Plane();
  upper->set_material(reflective);
  upper->SetTransform(Translation(0, 1, 0));
  w.add_object(upper);

  Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
  Color unused = w.ColorAt(r);
  ASSERT_TRUE(true);
}

TEST(WorldTest, MaximumRecursionRefletedColor) {
  World w = DefaultWorld();
  auto lower = new Plane();
  auto reflective = Material();
  reflective.set_reflective(1.0);
  lower->set_material(reflective);
  lower->SetTransform(Translation(0, -1, 0));
  w.add_object(lower);

  Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
  Intersections xs = w.Intersect(r);
  PreparedComputation pc = PreparedComputation(xs.Hit().value(), r, xs);
  Color reflected = w.ReflectedColor(pc, MAX_REFLECTIONS);
  ASSERT_EQ(Color(0, 0, 0), reflected);
}


TEST(WorldTest, RefractedColorOpaqueSurface) {
  auto w = DefaultWorld();
  auto shape = w.objects()[0];
  Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto allxs = w.Intersect(r);
  std::vector<Intersection> shape_xs;
  for (std::vector<Tuple>::size_type i = 0; i < allxs.Size(); ++i) {
    if (shape == allxs[i].Object()) {
      shape_xs.push_back(allxs[i]);
    }
  }
  auto xs = Intersections(shape_xs);
  auto pc = PreparedComputation(xs[0], r, xs);
  auto c = w.RefractedColor(pc, 0);
  ASSERT_EQ(Color(0, 0, 0), c);
}

TEST(WorldTest, MaxRefractedDepth) {
  auto dw = DefaultWorld();
  auto shape = dw.objects()[0];
  Material m = shape->material();
  m.set_transparency(1.0);
  m.set_refractive_index(REFRACTIVE_INDEX_GLASS);
  shape->set_material(m);

  World w = World();
  w.add_object(shape);
  w.add_object(dw.objects()[1]);

  Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto allxs = w.Intersect(r);
  std::vector<Intersection> shape_xs;
  for (std::vector<Tuple>::size_type i = 0; i < allxs.Size(); ++i) {
    if (shape == allxs[i].Object()) {
      shape_xs.push_back(allxs[i]);
    }
  }
  auto xs = Intersections(shape_xs);
  auto pc = PreparedComputation(xs[0], r, xs);
  auto c = w.RefractedColor(pc, MAX_REFRACTIONS);
  ASSERT_EQ(Color(0, 0, 0), c);
}

TEST(WorldTest, TotalInternalRefractionColor) {
  auto dw = DefaultWorld();
  auto shape = dw.objects()[0];
  Material m = shape->material();
  m.set_transparency(1.0);
  m.set_refractive_index(REFRACTIVE_INDEX_GLASS);
  shape->set_material(m);

  World w = World();
  w.add_object(shape);
  w.add_object(dw.objects()[1]);

  Ray r = Ray(Point(0, 0, sqrt(2.0) / 2.0), Vector(0, 1, 0));
  auto allxs = w.Intersect(r);
  std::vector<Intersection> shape_xs;
  for (std::vector<Tuple>::size_type i = 0; i < allxs.Size(); ++i) {
    if (shape == allxs[i].Object()) {
      shape_xs.push_back(allxs[i]);
    }
  }
  auto xs = Intersections(shape_xs);
  auto pc = PreparedComputation(xs[1], r, xs);
  auto c = w.RefractedColor(pc, 0);
  ASSERT_EQ(Color(0, 0, 0), c);
}

TEST(WorldTest, RefractedColor) {
  auto dw = DefaultWorld();
  auto a = dw.objects()[0];
  Material ma = a->material();
  ma.set_ambient(1.0);
  ma.set_pattern(new PatternMock());
  a->set_material(ma);

  auto b = dw.objects()[1];
  Material mb = Material();
  mb.set_transparency(1.0);
  mb.set_refractive_index(REFRACTIVE_INDEX_GLASS);
  b->set_material(mb);

  World w = World();
  w.add_object(a);
  w.add_object(b);

  Ray r = Ray(Point(0, 0, 0.1), Vector(0, 1, 0));
  Intersections xs = w.Intersect(r);
  auto pc = PreparedComputation(xs[2], r, xs);
  auto c = w.RefractedColor(pc, 0);
  ASSERT_EQ(c, Color(0, 0.998875, 0.0472185));
}

TEST(WorldTest, ShadeHitTransparency) {
  auto w = DefaultWorld();
  auto floor = new Plane();
  floor->SetTransform(Translation(0, -1, 0));
  auto floorm = Material();
  floorm.set_transparency(0.5);
  floorm.set_refractive_index(1.5);
  floor->set_material(floorm);
  w.add_object(floor);

  auto ball = new Sphere();
  ball-> SetTransform(Translation(0, -3.5, -0.5));
  auto ballm = Material();
  ballm.set_color(Color(1, 0, 0));
  ballm.set_ambient(0.5);
  ball->set_material(ballm);
  w.add_object(ball);

  Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
  Intersections xs = w.Intersect(r);
  ASSERT_EQ(xs[0].Object(), floor);

  auto pc = PreparedComputation(xs[0], r, xs);
  auto c = w.ShadeHit(pc, 0);
  ASSERT_EQ(c, Color(0.93642, 0.68642, 0.68642));
}

TEST(WorldTest, SchlickTotalInternalRefraction) {
  auto shape = GlassySphere();
  Ray r = Ray(Point(0, 0, sqrt(2.0) / 2.0), Vector(0, 1, 0));
  Intersections xs = Intersections(std::vector<Intersection> {
    Intersection(-sqrt(2.0) / 2.0, shape),
    Intersection(sqrt(2.0 ) / 2.0, shape)
  });
  auto pc = PreparedComputation(xs[1], r, xs);
  ASSERT_FLOAT_EQ(pc.schlick(), 1.0);
}

TEST(WorldTest, SchlickPerpendicular) {
  auto shape = GlassySphere();
  Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
  Intersections xs = Intersections(std::vector<Intersection> {
    Intersection(-1, shape),
    Intersection(1, shape)
  });
  auto pc = PreparedComputation(xs[1], r, xs);
  ASSERT_FLOAT_EQ(pc.schlick(), 0.040000003);
}

TEST(WorldTest, SchlickSmallAngleN2gtN1) {
  auto shape = GlassySphere();
  Ray r = Ray(Point(0, 0.99, -2), Vector(0, 0, 1));
  Intersections xs = Intersections(std::vector<Intersection> {
    Intersection(1.8589, shape),
  });
  auto pc = PreparedComputation(xs[0], r, xs);
  ASSERT_FLOAT_EQ(pc.schlick(), 0.4887307);
}

TEST(WorldTest, ShadeHitTransparentReflective) {
  auto w = DefaultWorld();
  auto floor = new Plane();
  floor->SetTransform(Translation(0, -1, 0));
  auto floorm = Material();
  floorm.set_reflective(0.5);
  floorm.set_transparency(0.5);
  floorm.set_refractive_index(1.5);
  floor->set_material(floorm);
  w.add_object(floor);

  auto ball = new Sphere();
  ball-> SetTransform(Translation(0, -3.5, -0.5));
  auto ballm = Material();
  ballm.set_color(Color(1, 0, 0));
  ballm.set_ambient(0.5);
  ball->set_material(ballm);
  w.add_object(ball);

  Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
  Intersections xs = w.Intersect(r);
  ASSERT_EQ(xs[0].Object(), floor);

  auto pc = PreparedComputation(xs[0], r, xs);
  auto c = w.ShadeHit(pc, 0);
  ASSERT_EQ(c, Color(0.933915, 0.696434, 0.692431));
}
