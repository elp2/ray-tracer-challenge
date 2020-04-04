#include "primitives/ray.h"

#include "primitives/matrix.h"

Ray::Ray() {
  origin_ = Point(0.0, 0.0, 0.0);
  direction_ = Vector(0.0, 0.0, 0.0);
}

Ray::Ray(Tuple origin, Tuple direction) {
  origin_ = origin;
  direction_ = direction;
}

Tuple Ray::Position(float t) const {
  return origin_ + direction_ * t;
}

const Ray Ray::Transform(const Matrix m) const {
  return Ray(m * origin_, m * direction_);
}

bool Ray::operator==(const Ray r) const {
  return origin_ == r.Origin() && direction_ == r.Direction();
}
