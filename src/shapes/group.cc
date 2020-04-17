#include "shapes/group.h"

#include "primitives/tuple.h"

Group::Group() {
  children_ = new std::vector<Shape *>();
}

void Group::ExtendBoundsForChild(Shape *child) {
  Bounds unit_bounds = child->UnitBounds();
  float xc = (unit_bounds.maximum().x() + unit_bounds.minimum().x()) / 2.0;
  float yc = (unit_bounds.maximum().y() + unit_bounds.minimum().y()) / 2.0;
  float zc = (unit_bounds.maximum().z() + unit_bounds.minimum().z()) / 2.0;

  float xd = unit_bounds.maximum().x() - xc;
  float yd = unit_bounds.maximum().y() - yc;
  float zd = unit_bounds.maximum().z() - zc;

  Tuple center_point = Point(xc, yc, zc);
  // TODO Problem is that we need to create a brand new bounds from all these values.
  Bounds child_bounds = Bounds(child->Transform() * center_point, child->Transform() * center_point);
  for (float x = -1; x < 2; x += 2) {
    for (float y = -1; y < 2; y += 2) {
      for (float z = -1; z < 2; z += 2) {
        Tuple corner_vector = Vector(x * xd, y * yd, z * zd);
        Tuple corner = center_point + corner_vector;
        Tuple transformed_corner = child->Transform() * corner;
        child_bounds.ExtendToFit(transformed_corner);
      }
    }
  }
  bounds_.MergeWith(child_bounds);
}

void Group::AddChild(Shape *child) {
  ExtendBoundsForChild(child);
  child->set_parent(this);
  children_->push_back(child);
}

const Intersections Group::ObjectIntersect(const Ray object_ray) const {
  auto xs = Intersections(std::vector<Intersection> {});
  for (const Shape* s : (*children_)) {
    xs.Merge(s->Intersect(object_ray));
  }
  return xs;
}

const Tuple Group::ObjectNormal(const Tuple object_point) const {
  return Point(0.0, 0.0, 0.0);
}

bool Group::operator==(const Group o) const {
  return Shape::operator==(o);
}

const Bounds Group::UnitBounds() const {
  return bounds_;
}
