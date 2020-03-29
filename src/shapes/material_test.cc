#include "gtest/gtest.h"

#include <math.h>

#include "primitives/color.h"

#include "shapes/material.h"

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

  Tuple result = m.Lighting(light, position, eye_vector, normal_vector);
  ASSERT_EQ(Color(1.9, 1.9, 1.9), result);
}

TEST(MaterialTest, EyeOffset45BetweenLightAndSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Point(0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, -10.0), Color(1.0, 1.0, 1.0));

  Tuple result = m.Lighting(light, position, eye_vector, normal_vector);
  ASSERT_EQ(Color(1.0, 1.0, 1.0), result);
}

TEST(MaterialTest, LightOffset45EyeOppositeSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Vector(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));

  Tuple result = m.Lighting(light, position, eye_vector, normal_vector);
  ASSERT_EQ(Color(0.7364, 0.7364, 0.7364), result);
}

TEST(MaterialTest, LightingInReflectionPathOfEye) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Vector(0.0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));

  Tuple result = m.Lighting(light, position, eye_vector, normal_vector);
  result.Debug();
  ASSERT_EQ(Color(1.63639, 1.63639, 1.63639), result);
}

TEST(MaterialTest, LightBehindSurface) {
  Material m = Material();
  Tuple position = Point(0.0, 0.0, 0.0);

  Tuple eye_vector = Point(0.0, 0.0, -1.0);
  Tuple normal_vector = Vector(0.0, 0.0, -1.0);
  PointLight light = PointLight(Point(0.0, 0.0, 10.0), Color(1.0, 1.0, 1.0));

  Tuple result = m.Lighting(light, position, eye_vector, normal_vector);

  ASSERT_EQ(Color(0.1, 0.1, 0.1), result);
  ASSERT_EQ(Color(m.ambient(), m.ambient(), m.ambient()), result);
}
