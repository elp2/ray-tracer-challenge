#include "primitives/intersections.h"

#include <cassert>

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

void Intersections::Merge(Intersections xs) {
  std::vector<Intersection> merged;
  std::vector<Intersection>::const_iterator xsi = xs.intersections_.begin();
  std::vector<Intersection>::const_iterator i = intersections_.begin();
  while (xsi != xs.intersections_.end() && i != intersections_.end()) {
    if ((*xsi).T() < (*i).T()) {
      merged.push_back(*xsi);
      ++xsi;
    } else {
      merged.push_back(*i);
      ++i;
    }
  }
  while (xsi != xs.intersections_.end()) {
    merged.push_back(*xsi);
    ++xsi;
  }
  while (i != intersections_.end()) {
    merged.push_back(*i);
    ++i;
  }
  intersections_ = merged;
}

Intersection Intersections::operator[](int index) {
  return intersections_[index];
}
