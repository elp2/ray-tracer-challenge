#include "lights/spot_light.h"

#include <cassert>

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

SpotLight::SpotLight(Tuple position, Color intensity, float center_radians, float total_radians) {
  position_ = position;
  intensity_ = intensity;

  assert(center_radians_ < total_radians_);
  assert(center_radians_ > M_PI / 20.0);
  assert(total_radians_ < M_PI / 2.0);

  center_radians_ = center_radians;
  total_radians_ = total_radians;
  shaded_radians = total_radians_ - center_radians_;
  lightlets_ = std::vector<const Lightlet*> { new SpotLightlet(position_, intensity_, 0.75) };
};

const std::vector<const Lightlet *> &SpotLight::LightletsForPoint(const Tuple &p) {
  /* TODO: Re-enable with angles.
  // Default fully shadowed.
  float shadowing = 1.0;
  // TODO: Calculate incoming angle.
  float hit_angle = M_PI / 7.5;
  hit_angle = fabs(hit_angle);
  if (hit_angle < center_radians_) {
    shadowing = 0.0;
  } else if (hit_angle < total_radians_) {
    // Fade 0.0 -> 1.0 linearly.
    float distance = hit_angle - center_radians_;
    shadowing = distance / shaded_radians;
  }
  lightlets_ = std::vector<const Lightlet*> { new SpotLightlet(position_, intensity_, shadowing) };
  */
  return lightlets_;
}

bool SpotLight::operator==(const SpotLight &other) const {
  return other.intensity_ == intensity_ && other.position_ == position_
      && other.center_radians_ == center_radians_ && other.total_radians_ == total_radians_;
}

bool SpotLight::operator!=(const SpotLight &other) const {
  return !(other == *this);
}
