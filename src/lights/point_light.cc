#include "lights/point_light.h"

bool PointLight::operator==(const PointLight other) const {
  return other.intensity() == intensity_ && other.position() == position_;
}
