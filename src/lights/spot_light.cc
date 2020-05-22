#include "lights/spot_light.h"

#include <cassert>
#include <iostream>
#include <math.h>

class SpotLightlet : public Lightlet {
 public:
  SpotLightlet(Tuple position, Color intensity, float shadowing) {
    position_ = position;
    intensity_ = intensity;
    shadowing_ = shadowing;
  };
  ~SpotLightlet() = default;

  float ShadowingForPoint(const Tuple &point) const { (void)point; return shadowing_; };

 private:
  float shadowing_ = 0.0;
};

SpotLight::SpotLight(Tuple position, Color intensity, float center_radians, float total_radians, const Tuple &facing) {
  position_ = position;
  facing_vector_ = (facing - position_).Normalized();
  intensity_ = intensity;

  center_radians_ = center_radians;
  total_radians_ = total_radians;
  shaded_radians = total_radians_ - center_radians_;

  assert(center_radians_ < total_radians_);
  assert(center_radians_ > M_PI / 40.0);
  assert(total_radians_ < M_PI / 4.0);
};

const std::vector<const Lightlet *> *SpotLight::LightletsForPoint(const Tuple &p) {
  // Default fully shadowed.
  float shadowing = 1.0;
  Tuple point_vector = p - position_;
  float cos_radians = point_vector.Normalized().Dot(facing_vector_);
  float hit_radians = acos(cos_radians);
  assert(hit_radians >= 0);

  if (hit_radians < center_radians_) {
    shadowing = 0.0;
  } else if (hit_radians < total_radians_) {
    // Fade 0.0 -> 1.0 linearly.
    float distance = hit_radians - center_radians_;
    shadowing = distance / shaded_radians;
  }
  // TODO: Free these properly.
  return new std::vector<const Lightlet*> { new SpotLightlet(position_, intensity_, shadowing) };
}

bool SpotLight::operator==(const SpotLight &other) const {
  return other.intensity_ == intensity_ && other.position_ == position_
      && other.center_radians_ == center_radians_ && other.total_radians_ == total_radians_;
}

bool SpotLight::operator!=(const SpotLight &other) const {
  return !(other == *this);
}
