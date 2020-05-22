#include "lights/area_light.h"

#include "lights/lightlet.h"

#include <cassert>
#include <iostream>

class AreaLightlet : public Lightlet {
 public:
  AreaLightlet(Tuple position, Color intensity) { position_ = position; intensity_ = intensity; };
  ~AreaLightlet() = default;

  float ShadowingForPoint(const Tuple &point) const { (void)point; return 0.0; };
};

AreaLight::AreaLight(Tuple position, Color intensity, float radius, int arm_lights) {
  position_ = position;
  intensity_ = intensity;
  radius_ = radius;
  arm_lights_ = arm_lights;

  assert(arm_lights_ > 1);
  float step = (2 * radius) / (float)(arm_lights - 1);
  for (float x = -radius; x <= radius; x += step) {
    for (float y = -radius; y <= radius; y += step) {
      for (float z = -radius; z <= radius; z += step) {
        Tuple pos = position_ - Vector(x, y, z);
        std::cout << "Area Lightlet: " << pos.DebugString() << std::endl;
        lightlets_.push_back(new AreaLightlet(pos, intensity_));
      }
    }
  }
};

bool AreaLight::operator==(const AreaLight &other) const {
  return other.intensity_ == intensity_ && other.position_ == position_
      && other.radius_ == radius_ && other.arm_lights_ == arm_lights_;
}

bool AreaLight::operator!=(const AreaLight &other) const {
  return !(other == *this);
}
