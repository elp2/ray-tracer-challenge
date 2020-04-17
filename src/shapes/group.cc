#include "shapes/group.h"

#include "primitives/math.h"
#include "primitives/tuple.h"

#include <algorithm>
#include <math.h>

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

const void Group::CheckAxis(const float &origin, const float &direction, float *tmin, float *tmax,
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

const Tuple Group::ObjectNormal(const Tuple object_point) const {
  return Point(0.0, 0.0, 0.0);
}

bool Group::operator==(const Group o) const {
  return Shape::operator==(o);
}

const Bounds Group::UnitBounds() const {
  return bounds_;
}
