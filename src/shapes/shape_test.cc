#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/shape.h"

class ShapeMock : public Shape {
 public:
  MOCK_METHOD(const Intersections, ObjectIntersect, (const Ray object_ray), (const, override));
  const Tuple ObjectNormal(const Tuple object_point) const {
    return Vector(object_point.x(), object_point.y(), object_point.z());
  };
};

class ShapeTest : public ::testing::Test {
 protected:
  ShapeTest() {};
  ~ShapeTest() {};
};

TEST(ShapeTest, DefaultTransformation) {
  ShapeMock sm = ShapeMock();
  ASSERT_EQ(sm.Transform(), IdentityMatrix(4));
};

TEST(ShapeTest, AssignsTransformation) {
  ShapeMock sm = ShapeMock();
  sm.SetTransform(Translation(2.0, 3.0, 4.0));
  ASSERT_EQ(sm.Transform(), Translation(2.0, 3.0, 4.0));
};

TEST(ShapeTest, DefaultMaterial) {
  ShapeMock sm = ShapeMock();
  ASSERT_EQ(sm.material(), Material());
};

TEST(ShapeTest, AssignsMaterial) {
  ShapeMock sm = ShapeMock();
  Material m = Material();
  m.set_ambient(1.0);
  sm.set_material(m);
  ASSERT_EQ(sm.material(), m);
};

TEST(ShapeTest, IntersectScaledShape) {
  ShapeMock sm = ShapeMock();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  sm.SetTransform(Scaling(2.0, 2.0, 2.0));
  const Ray expected_ray = Ray(Point(0.0, 0.0, -2.5), Vector(0.0, 0.0, 0.5));
  EXPECT_CALL(sm, ObjectIntersect(expected_ray)).WillOnce(
    ::testing::Return(Intersections(std::vector<Intersection> {})));
  sm.Intersect(r);
};

TEST(ShapeTest, IntersectTranslatedShape) {
  ShapeMock sm = ShapeMock();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  sm.SetTransform(Translation(5.0, 0.0, 0.0));
  const Ray expected_ray = Ray(Point(-5.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  EXPECT_CALL(sm, ObjectIntersect(expected_ray)).WillOnce(
    ::testing::Return(Intersections(std::vector<Intersection> {})));
  sm.Intersect(r);
};

TEST(ShapeTest, NormaltScaledShape) {
  ShapeMock sm = ShapeMock();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  sm.SetTransform(Scaling(1.0, 0.5, 1.0) * RotationZ(M_PI / 5.0));
  Tuple at = Point(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0);
  EXPECT_EQ(sm.Normal(at), Vector(0.0, 0.97014, 0.24254));
};

TEST(ShapeTest, NormalTranslatedShape) {
  ShapeMock sm = ShapeMock();
  sm.SetTransform(Translation(0.0, 1.0, 0.0));
  EXPECT_EQ(sm.Normal(Point(0.0, 1.70711, -0.70711)), Vector(0.0, 0.70711, -0.70711));
};
