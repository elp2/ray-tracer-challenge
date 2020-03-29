#ifndef RTC_LIGHTS_POINT_LIGHT_H
#define RTC_LIGHTS_POINT_LIGHT_H

#include "primitives/color.h"
#include "primitives/tuple.h"

class PointLight {
 public:
  PointLight() {};
  PointLight(Tuple position, Color intensity) { position_ = position; intensity_ = intensity; };
  ~PointLight() = default;

  Tuple position() const { return position_; };
  Color intensity() const { return intensity_; };
  bool operator==(const PointLight other) const;

 private:
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);
};

#endif    // RTC_LIGHTS_POINT_LIGHT_H
