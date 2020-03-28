#ifndef RTC_LIGHTS_POINT_LIGHT_H
#define RTC_LIGHTS_POINT_LIGHT_H

#include "primitives/color.h"
#include "primitives/tuple.h"

class PointLight {
 public:
  PointLight(Tuple position, Color intensity) { position_ = position; intensity_ = intensity; };
  ~PointLight() = default;

  Tuple position() { return position_; };
  Color intensity() { return intensity_; };

 private:
  Tuple position_;
  Color intensity_;
};

#endif    // RTC_LIGHTS_POINT_LIGHT_H
