#include "shapes/bounds.h"

#include <iostream>
#include <math.h>

#include "primitives/transformation.h"

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

const Matrix Bounds::UnitifyTransform(bool unitify_x, bool unitify_y, bool unitify_z) const {
  float x_width = maximum().x() - minimum().x();
  float y_width = maximum().y() - minimum().y();
  float z_width = maximum().z() - minimum().z();

  Matrix translation = Translation(
      -minimum().x() - x_width / 2.0,
      -minimum().y() - y_width / 2.0,
      -minimum().z() - z_width / 2.0);

  if (!unitify_x && !unitify_y && !unitify_z) {
    return translation;
  }
  float x_scale = 2.0 / x_width;
  float y_scale = 2.0 / y_width;
  float z_scale = 2.0 / z_width;

  float scale = std::min(unitify_x ? x_scale : INFINITY,
      std::min(unitify_y ? y_scale : INFINITY, unitify_z ? z_scale : INFINITY));
  Matrix scaling = Scaling(scale, scale, scale);

  return scaling * translation;
}