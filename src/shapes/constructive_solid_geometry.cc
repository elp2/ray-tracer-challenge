#include "shapes/constructive_solid_geometry.h"

#include "primitives/intersection.h"
#include "primitives/math.h"

#include <algorithm>
#include <cassert>
#include <math.h>
#include <utility>

ConstructiveSolidGeometry::ConstructiveSolidGeometry(Shape *left, Shape *right,
    IntersectionStrategy *intersection_strategy) {
  left_ = left;
  left_->set_parent(this);
  right_ = right;
  right_->set_parent(this);
  intersection_strategy_ = intersection_strategy;
}

const Intersections ConstructiveSolidGeometry::ObjectIntersect(const Ray object_ray) const {
  Intersections xs = left_->Intersect(object_ray);
  xs.Merge(right_->Intersect(object_ray));
  return FilterIntersections(xs);
}

const Tuple ConstructiveSolidGeometry::ObjectNormal(const Tuple &object_point, const Intersection &i) const {
  assert(false);
  return Vector(0, 0, object_point.z());
}

const Intersections ConstructiveSolidGeometry::FilterIntersections(Intersections &xs) const {
  std::vector<Intersection> filtered;
  bool in_left = false;
  bool in_right = false;

  for (auto hit : xs.intersections()) {
    Shape *hit_shape = (Shape *)hit.Object();
    bool left_hit = left_->Includes(hit_shape);

    if (intersection_strategy_->IntersectionAllowed(left_hit, in_left, in_right)) {
      filtered.push_back(hit);
    }
    if (left_hit) {
      in_left = !in_left;
    } else {
      in_right = !in_right;
    }
  }

  return Intersections(filtered);
}

bool ConstructiveSolidGeometry::Includes(Shape *other) {
  return left_->Includes(other) || right_->Includes(other);
}

bool ConstructiveSolidGeometry::operator==(const ConstructiveSolidGeometry o) const {
  return Shape::operator==(o) && o.left_ == left_ && o.right_ == right_;
}

const Bounds ConstructiveSolidGeometry::UnitBounds() const {
  Bounds bounds = ChildBounds(left_);
  bounds.MergeWith(ChildBounds(right_));
  return bounds;
}
