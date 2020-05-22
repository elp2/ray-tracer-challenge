#ifndef RTC_LIGHTS_SPOT_LIGHT_H
#define RTC_LIGHTS_SPOT_LIGHT_H

#include "lights/light.h"
#include "lights/lightlet.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <math.h>
#include <vector>

static const float MAX_TOTAL_RADIANS = M_PI / 4.0;
static const float DEFAULT_TOTAL_RADIANS = M_PI / 6.0;
static const float DEFAULT_CENTER_RADIANS = M_PI / 9.0;

class SpotLight : public Light {
 public:
  SpotLight(Tuple position, Color intensity, float center_radians, float total_radians);
  SpotLight() : SpotLight(Point(0, 0, 0), Color(1, 1, 1)) {};
  SpotLight(Tuple position, Color intensity) :
      SpotLight(position, intensity, DEFAULT_CENTER_RADIANS, DEFAULT_TOTAL_RADIANS) {};
  ~SpotLight() = default;

  bool operator!=(const SpotLight &other) const;
  bool operator==(const SpotLight &other) const;

  const std::vector<const Lightlet *> &LightletsForPoint(const Tuple &p);

 private:
  float total_radians_ = DEFAULT_TOTAL_RADIANS;
  float center_radians_ = DEFAULT_CENTER_RADIANS;
  float shaded_radians = 0.0;
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);

  // TODO: constantly re-assigning this probably isn't great.
  std::vector<const Lightlet *> lightlets_;
};

#endif    // RTC_LIGHTS_SPOT_LIGHT_H
