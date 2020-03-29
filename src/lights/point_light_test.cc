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
  ASSERT_EQ(point_light.position(), position);
  ASSERT_EQ(point_light.intensity(), intensity);
}