#ifndef RTC_LIGHTS_AREA_LIGHT_H
#define RTC_LIGHTS_AREA_LIGHT_H

#include "lights/light.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <vector>

static const float AREA_LIGHT_RADIUS = 0.1;
static const int AREA_LIGHT_ARM_LIGHTS = 3;

class AreaLight : public Light {
 public:
  AreaLight() : AreaLight(Point(1, 5, 1), Color(1, 1, 1), AREA_LIGHT_RADIUS, AREA_LIGHT_ARM_LIGHTS) {};
  AreaLight(Tuple position, Color intensity, float radius, int arm_lights);
  ~AreaLight() = default;

  bool operator!=(const AreaLight &other) const;
  bool operator==(const AreaLight &other) const;

  const std::vector<const Lightlet *> &LightletsForPoint(const Tuple &p) { (void)p; return lightlets_; };

 private:
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);
  std::vector<const Lightlet *> lightlets_;
  float radius_ = AREA_LIGHT_RADIUS;
  int arm_lights_ = AREA_LIGHT_ARM_LIGHTS;
};

#endif    // RTC_LIGHTS_AREA_LIGHT_H
