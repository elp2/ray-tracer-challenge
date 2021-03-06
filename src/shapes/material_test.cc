#include "gtest/gtest.h"

#include <math.h>

#include "primitives/color.h"

#include "lights/point_light.h"
#include "patterns/striped_pattern.h"
#include "shapes/material.h"
#include "shapes/sphere.h"

class MaterialTest : public ::testing::Test {
 protected:
  MaterialTest() {};
  ~MaterialTest() {};
};

TEST(MaterialTest, DefaultMaterial) {
  Material m = Material();
  ASSERT_EQ(m.color(), Color(1.0, 1.0, 1.0));
  ASSERT_FLOAT_EQ(m.ambient(), 0.1);
  ASSERT_FLOAT_EQ(m.diffuse(), 0.9);
  ASSERT_FLOAT_EQ(m.specular(), 0.9);
  ASSERT_FLOAT_EQ(m.shininess(), 200.0);
}

TEST(MaterialTest, EyeBetweenLightAndSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Vector(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 0.0, new Sphere());
  ASSERT_EQ(Color(1.9, 1.9, 1.9), result);
}

TEST(MaterialTest, EyeOffset45BetweenLightAndSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Point(0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 0.0, new Sphere());
  ASSERT_EQ(Color(1.0, 1.0, 1.0), result);
}

TEST(MaterialTest, LightOffset45EyeOppositeSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Vector(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 0.0, new Sphere());
  ASSERT_EQ(Color(0.7364, 0.7364, 0.7364), result);
}

TEST(MaterialTest, LightingInReflectionPathOfEye) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Vector(0.0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 0.0, new Sphere());
  ASSERT_EQ(Color(1.63639, 1.63639, 1.63639), result);
}

TEST(MaterialTest, LightBehindSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Point(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, 10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 0.0, new Sphere());

  ASSERT_EQ(Color(0.1, 0.1, 0.1), result);
  ASSERT_EQ(Color(m.ambient(), m.ambient(), m.ambient()), result);
}

TEST(MaterialTest, LightingInShadow) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Point(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(position))[0];

  Tuple result = m.Lighting(lightlet, position, eye_vector, normal_vector, 1.0, new Sphere());

  ASSERT_EQ(Color(0.1, 0.1, 0.1), result);
}

TEST(MaterialTest, LightingWithPattern) {
  Material m = Material();
  m.set_ambient(1.0);
  m.set_diffuse(0);
  m.set_specular(0);

  Color red = Color(1, 0, 0);
  Color blue = Color(0, 0, 1);
  Pattern *pattern = new StripedPattern(red, blue);
  m.set_pattern(pattern);

  Tuple eye_vector = Point(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0));
  auto lightlet = (*light.LightletsForPoint(Point(0, 0, 0)))[0];

  Tuple p1 = Point(0.9, 0.0, 0.0);
  ASSERT_EQ(red, m.Lighting(lightlet, p1, eye_vector, normal_vector, 0.0, new Sphere()));

  Tuple p2 = Point(1.9, 0.0, 0.0);
  ASSERT_EQ(blue, m.Lighting(lightlet, p2, eye_vector, normal_vector, 0.0, new Sphere()));
}

TEST(MaterialTest, ReflectivityOfDefaultMaterial) {
  Material m = Material();
  ASSERT_FLOAT_EQ(m.reflective(), 0);
}
