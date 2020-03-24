#include "primitives/intersections.h"

Intersections::Intersections(std::vector<Intersection> intersections) {
  intersections_ = intersections;
}

std::optional<Intersection> Intersections::Hit() const {
  if (!intersections_.size()) {
    return std::nullopt;
  }

  std::optional<Intersection> hit = std::nullopt;
  for (std::vector<Intersection>::const_iterator i = intersections_.begin();
    i != intersections_.end(); ++i) {
      if ((*i).T() < 0) {
        continue;
      }
      if (hit == std::nullopt || hit.value().T() > (*i).T()) {
        hit = std::optional<Intersection>(*i);
      }
  }
  return hit;
}

Intersection Intersections::operator[](int index) {
  return intersections_[index];
}
