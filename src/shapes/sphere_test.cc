#include "gtest/gtest.h"

#include "primitives/ray.h"
#include "shapes/sphere.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class SphereTest : public ::testing::Test {
 protected:
  SphereTest() {};
  ~SphereTest() {};
};

TEST(SphereTest, IntersectsTwoPointsStraightOn) {
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 6.0);
}

TEST(SphereTest, IntersectsAtTangent) {
  Ray r = Ray(TupleFromPoint(0, 1, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), 5.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 5.0);
}

TEST(SphereTest, MissesSphere) {
  Ray r = Ray(TupleFromPoint(0, 2, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(0, xs.Size());
}

TEST(SphereTest, OriginatesInSphere) {
  Ray r = Ray(TupleFromPoint(0, 0, 0), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), -1.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 1.0);
}

TEST(SphereTest, SphereBehindRay) {
  Ray r = Ray(TupleFromPoint(0, 0, 5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_FLOAT_EQ(xs[0].T(), -6.0);
  ASSERT_FLOAT_EQ(xs[1].T(), -4.0);
}

TEST(SphereTest, ObjectSetOnIntersection) {
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Sphere s = Sphere();
  Intersections xs = s.Intersect(r);

  ASSERT_EQ(2, xs.Size());
  ASSERT_EQ(xs[0].Object(), &s);
  ASSERT_EQ(xs[1].Object(), &s);
}

TEST(SphereTest, StartsWithIdentity) {
  Sphere s = Sphere();
  ASSERT_EQ(s.Transform(), IdentityMatrix(4));
}

TEST(SphereTest, IntersectsScaling) {
  Sphere s = Sphere();
  s.SetTransform(Scaling(2, 2, 2));
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Intersections xs = s.Intersect(r);
  ASSERT_EQ(xs.Size(), 2);
  ASSERT_FLOAT_EQ(xs[0].T(), 3);
  ASSERT_FLOAT_EQ(xs[1].T(), 7);
}

TEST(SphereTest, DoesntIntersectTranslation) {
  Sphere s = Sphere();
  s.SetTransform(Translation(5, 0, 0));
  Ray r = Ray(TupleFromPoint(0, 0, -5), TupleFromVector(0, 0, 1));
  Intersections xs = s.Intersect(r);
  ASSERT_EQ(xs.Size(), 0);
}

TEST(SphereTest, NormalXAxis) {
  Sphere s = Sphere();
  Tuple n = s.Normal(TupleFromPoint(1, 0, 0));
  ASSERT_EQ(TupleFromVector(1, 0, 0), n);
}

TEST(SphereTest, NormalYAxis) {
  Sphere s = Sphere();
  Tuple n = s.Normal(TupleFromPoint(0, 1, 0));
  ASSERT_EQ(TupleFromVector(0, 1, 0), n);
}

TEST(SphereTest, NormalZAxis) {
  Sphere s = Sphere();
  Tuple n = s.Normal(TupleFromPoint(0, 0, 1));
  ASSERT_EQ(TupleFromVector(0, 0, 1), n);
}

TEST(SphereTest, PointIsANormalizedVector) {
  Sphere s = Sphere();
  Tuple n = s.Normal(TupleFromPoint(sqrt(3) / 3.0, sqrt(3) / 3.0, sqrt(3) / 3.0));
  ASSERT_EQ(n.Normalized(), n);
}

TEST(SphereTest, TranslatedSphereNormal) {
  Sphere s = Sphere();
  s.SetTransform(Translation(0.0, 1.0, 0.0));
  Tuple n = s.Normal(TupleFromPoint(0, 1.70711, -0.70711));
  ASSERT_EQ(TupleFromVector(0, 0.70711, -0.70711), n);
}

TEST(SphereTest, ScaledRotatedSphereNormal) {
  Sphere s = Sphere();
  s.SetTransform(Scaling(1.0, 0.5, 1.0) * RotationZ(M_PI / 5.0));
  Tuple n = s.Normal(TupleFromPoint(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0));
  ASSERT_EQ(TupleFromVector(0.0, 0.97014, -0.24254), n);
}

TEST(SphereTest, HasMaterial) {
  Sphere s = Sphere();
  ASSERT_EQ(s.material(), Material());
}

TEST(SphereTest, SetsMaterial) {
  Sphere s = Sphere();
  Material m = Material();
  m.set_ambient(1.0);
  s.set_material(m);
  ASSERT_EQ(s.material(), m);
}

TEST(SphereTest, Equals) {
  Sphere s1 = Sphere();
  Material m1 = Material();
  m1.set_color(Color(0.8, 1.0, 0.6));
  m1.set_diffuse(0.7);
  m1.set_specular(0.2);
  s1.set_material(m1);

  Sphere s2 = Sphere();
  Material m2 = Material();
  m2.set_color(Color(0.8, 1.0, 0.6));
  m2.set_diffuse(0.7);
  m2.set_specular(0.2);
  s2.set_material(m2);

  ASSERT_EQ(s1, s2);
}
