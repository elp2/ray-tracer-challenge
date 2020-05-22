#ifndef RTC_LIGHTS_SPOT_LIGHT_H
#define RTC_LIGHTS_SPOT_LIGHT_H

#include "lights/light.h"
#include "lights/lightlet.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

static const float MAX_TOTAL_RADIANS = M_PI / 8.0;
static const float DEFAULT_TOTAL_RADIANS = M_PI / 12.0;
static const float DEFAULT_CENTER_RADIANS = M_PI / 18.0;

class SpotLight : public Light {
 public:
  SpotLight(Tuple position, Color intensity, float center_radians, float total_radians, const Tuple &facing);
  SpotLight(Tuple position, Color intensity, const Tuple &facing) :
      SpotLight(position, intensity, DEFAULT_CENTER_RADIANS, DEFAULT_TOTAL_RADIANS, facing) {};
  ~SpotLight() = default;

  bool operator!=(const SpotLight &other) const;
  bool operator==(const SpotLight &other) const;

  const std::vector<const Lightlet *> *LightletsForPoint(const Tuple &p);

 private:
  Tuple facing_vector_;
  float total_radians_;
  float center_radians_;
  float shaded_radians = 0.0;
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);
};

#endif    // RTC_LIGHTS_SPOT_LIGHT_H
