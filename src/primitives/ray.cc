#include "primitives/ray.h"

Ray::Ray(Tuple origin, Tuple direction) {
  origin_ = origin;
  direction_ = direction;
}

Tuple Ray::Position(float t) {
  return origin_ + direction_ * t;
}
