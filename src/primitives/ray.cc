#include "primitives/ray.h"

#include "primitives/matrix.h"

Ray::Ray(Tuple origin, Tuple direction) {
  origin_ = origin;
  direction_ = direction;
}

Tuple Ray::Position(float t) {
  return origin_ + direction_ * t;
}

Ray Ray::Transform(Matrix m) {
  return Ray(m * origin_, m * direction_);
}
