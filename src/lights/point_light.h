#ifndef RTC_LIGHTS_POINT_LIGHT_H
#define RTC_LIGHTS_POINT_LIGHT_H

#include "lights/lightlet.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <vector>

class PointLight {
 public:
  PointLight() : PointLight(Point(0, 0, 0), Color(1, 1, 1)) {};
  PointLight(Tuple position, Color intensity);
  ~PointLight() = default;

  bool operator!=(const PointLight &other) const;
  bool operator==(const PointLight &other) const;

  const std::vector<const Lightlet *> &LightletsForPoint(const Tuple &p) { (void)p; return lightlets_; };

 private:
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);
  std::vector<const Lightlet *> lightlets_;
};

#endif    // RTC_LIGHTS_POINT_LIGHT_H
