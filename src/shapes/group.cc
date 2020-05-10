#include "shapes/group.h"

#include "primitives/math.h"
#include "primitives/tuple.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <math.h>

Group::Group() {
  children_ = new std::vector<Shape *>();
}

Group::Group(Material material) {
  children_ = new std::vector<Shape *>();
  material_ = material;
}

void Group::ExtendBoundsForChild(Shape *child) {
  Bounds child_bounds = ChildBounds(child);
  bounds_.MergeWith(child_bounds);
}

void Group::AddChild(Shape *child) {
  ExtendBoundsForChild(child);
  child->set_parent(this);
  child->set_material(material_);
  children_->push_back(child);
}

const Intersections Group::ObjectIntersect(const Ray object_ray) const {
  float xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;

  CheckAxis(object_ray.Origin().x(), object_ray.Direction().x(), &xtmin, &xtmax,
      bounds_.minimum().x(), bounds_.maximum().x());
  CheckAxis(object_ray.Origin().y(), object_ray.Direction().y(), &ytmin, &ytmax,
      bounds_.minimum().y(), bounds_.maximum().y());
  CheckAxis(object_ray.Origin().z(), object_ray.Direction().z(), &ztmin, &ztmax,
      bounds_.minimum().z(), bounds_.maximum().z());

  float tmin = std::fmax(xtmin, std::fmax(ytmin, ztmin));
  float tmax = std::fmin(xtmax, std::fmin(ytmax, ztmax));

  if (tmin > tmax) {
    // Did not intersect bounding box.
    return Intersections(std::vector<Intersection> {});
  }

  auto xs = Intersections(std::vector<Intersection> {});
  for (const Shape* s : (*children_)) {
    xs.Merge(s->Intersect(object_ray));
  }
  return xs;
}

void Group::CheckAxis(const float &origin, const float &direction, float *tmin, float *tmax,
    const float &direction_min, const float &direction_max) const {
  float tmin_numerator = (direction_min - origin);
  float tmax_numerator = (direction_max - origin);

  if (fabs(direction) >= EPSILON) {
    *tmin = tmin_numerator / direction;
    *tmax = tmax_numerator / direction;
  } else {
    *tmin = tmin_numerator * INFINITY;
    *tmax = tmax_numerator * INFINITY;
  }
  if (*tmin > *tmax) {
    std::swap(*tmax, *tmin);
  }
}

const Tuple Group::ObjectNormal(const Tuple &object_point, const Intersection &i) const {
  // This should never be called since only its children should be in an intersection.
  (void)object_point;
  (void)i;
  assert(false);
  return Point(0.0, 0.0, 0.0);
}

bool Group::operator==(const Group o) const {
  return Shape::operator==(o);
}

const Bounds Group::UnitBounds() const {
  return bounds_;
}

Group *Group::OptimizedSubgroups(int groups_per_dimension) {
  std::vector<Group *> subgroups;
  for (int i = 0; i < groups_per_dimension * groups_per_dimension * groups_per_dimension; ++i) {
    subgroups.push_back(new Group(material_));
  }

  Tuple span = bounds_.maximum() - bounds_.minimum();

  for (auto child : (*children_)) {
    Bounds child_bounds = ChildBounds(child);
    Tuple center = child_bounds.center();
    int x = (int)(center.x() - bounds_.minimum().x()) * ((float)groups_per_dimension / span.x());
    int y = (int)(center.y() - bounds_.minimum().y()) * ((float)groups_per_dimension / span.y());
    int z = (int)(center.z() - bounds_.minimum().z()) * ((float)groups_per_dimension / span.z());

    std::vector<Group*>::size_type idx = 
        x * groups_per_dimension * groups_per_dimension + y * groups_per_dimension + z;
    assert(idx < subgroups.size());
    subgroups[idx]->AddChild(child);
  }

  auto ret = new Group(material_);
  for (auto subgroup : subgroups) {
    if (subgroup->size() > 0) {
      std::cout << "Subgroup size: " << subgroup->size() << std::endl;
      ret->AddChild(subgroup);
    }
  }

  return ret;
}

bool Group::Includes(Shape *other) {
  for (auto child : (*children_)) {
    if (child->Includes(other)) {
      return true;
    }
  }
  return false;
}
