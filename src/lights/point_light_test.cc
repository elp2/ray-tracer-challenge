#include "gtest/gtest.h"

#include "primitives/color.h"
#include "primitives/tuple.h"
#include "lights/point_light.h"

#include <math.h>
#include <vector>

class PointLightTest : public ::testing::Test {
 protected:
  PointLightTest() {};
  ~PointLightTest() {};
};

TEST(PointLightTest, HasPositionAndIntensity) {
  Color intensity = Color(1.0, 0.0, 0.0);
  Tuple position = Point(0.0, 0.0, 0.0);
  PointLight point_light = PointLight(position, intensity);
  auto lightlets = point_light.LightletsForPoint(Point(0, 0, 0));
  ASSERT_EQ(lightlets->size(), 1);
  auto lightlet = (*lightlets)[0];
  ASSERT_EQ(lightlet->position(), position);
  ASSERT_EQ(lightlet->intensity(), intensity);
}

TEST(PointLightTest, TestEquality) {
  Color ia = Color(0.0, 0.0, 0.0);
  Color ib = Color(1.0, 0.0, 0.0);
  Tuple pa = Point(0.0, 0.0, 0.0);
  Tuple pb = Point(1.0, 0.0, 0.0);

  EXPECT_NE(PointLight(pa, ia), PointLight(pb, ia));
  EXPECT_NE(PointLight(pa, ia), PointLight(pa, ib));

  EXPECT_EQ(PointLight(pa, ia), PointLight(pa, ia));
  EXPECT_EQ(PointLight(pb, ib), PointLight(pb, ib));
}
