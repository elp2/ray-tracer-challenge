#include "shapes/bounds.h"

#include <math.h>

Bounds::Bounds(Tuple minimum, Tuple maximum) {
  minimum_ = minimum;
  maximum_ = maximum;
}

void Bounds::ExtendToFit(const Tuple &point) {
  minimum_ = Point(std::min(point.x(), minimum_.x()),
      std::min(point.y(), minimum_.y()),
      std::min(point.z(), minimum_.z()));

  maximum_ = Point(std::max(point.x(), maximum_.x()),
      std::max(point.y(), maximum_.y()),
      std::max(point.z(), maximum_.z()));
}

void Bounds::MergeWith(const Bounds &other) {
  if (minimum_ == Point(0, 0, 0) && maximum_ == Point(0, 0, 0)) {
    // Empty bounds should merge with new bounds.
    minimum_ = other.minimum();
    maximum_ = other.maximum();
    return;
  }

  minimum_ = Point(std::min(other.minimum().x(), minimum_.x()),
      std::min(other.minimum().y(), minimum_.y()),
      std::min(other.minimum().z(), minimum_.z()));

  maximum_ = Point(std::max(other.maximum().x(), maximum_.x()),
      std::max(other.maximum().y(), maximum_.y()),
      std::max(other.maximum().z(), maximum_.z()));
}

const Tuple Bounds::center() const {
  return (maximum_ + minimum_) * 0.5;
}
