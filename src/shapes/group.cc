#include "shapes/group.h"

#include "primitives/tuple.h"

Group::Group() {
  children_ = new std::vector<Shape *>();
}

void Group::AddChild(Shape *child) {
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
