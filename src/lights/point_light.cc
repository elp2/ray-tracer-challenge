#include "lights/point_light.h"

class PointLightlet : public Lightlet {
 public:
  PointLightlet(Tuple position, Color intensity) { position_ = position; intensity_ = intensity; };
  ~PointLightlet() = default;

  float ShadowingForPoint(const Tuple &point) const { (void)point; return 0.0; };
};

PointLight::PointLight(Tuple position, Color intensity) {
  position_ = position;
  intensity_ = intensity;
  lightlets_ = std::vector<const Lightlet *> { new PointLightlet(position, intensity_) };
};

bool PointLight::operator==(const PointLight &other) const {
  return other.intensity_ == intensity_ && other.position_ == position_;
}

bool PointLight::operator!=(const PointLight &other) const {
  return !(other == *this);
}
