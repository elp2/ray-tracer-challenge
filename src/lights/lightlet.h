#ifndef RTC_LIGHTS_LIGHTLET_H
#define RTC_LIGHTS_LIGHTLET_H

#include "primitives/color.h"
#include "primitives/tuple.h"

class Lightlet {
 public:
  ~Lightlet() = default;

  // Returns how shadowed the point would be for this light.
  // For example if the light is not shining at all or directly at this point.
  virtual float ShadowingForPoint(const Tuple &point) const  = 0;
  Tuple position() const { return position_; };
  Color intensity() const { return intensity_; };

 protected:
  Tuple position_ = Point(0.0, 0.0, 0.0);
  Color intensity_ = Color(1.0, 1.0, 1.0);
};

#endif    // RTC_LIGHTS_LIGHTLET_H
