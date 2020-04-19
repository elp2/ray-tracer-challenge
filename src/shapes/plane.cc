#include "shapes/plane.h"

#include <math.h>

#include "primitives/intersections.h"
#include "primitives/math.h"
#include "primitives/ray.h"
#include "primitives/tuple.h"

const Intersections Plane::ObjectIntersect(const Ray object_ray) const {
  if (fabs(object_ray.Direction().y()) < EPSILON) {
    // Parallel to xz plane after translation. No intersections.
    return Intersections(std::vector<Intersection> {});
  }

  float t = -object_ray.Origin().y() / object_ray.Direction().y();
  Intersection x = Intersection(t, this);
  return Intersections(std::vector<Intersection> {x});
}

const Tuple Plane::ObjectNormal(const Tuple &object_point, const Intersection &i) const {
  return Vector(0.0, 1.0, 0.0);
}

bool Plane::operator==(const Plane o) const {
  return Shape::operator==(o);
}

const Bounds Plane::UnitBounds() const {
  return Bounds(Point(-GROUP_INFINITE_BIGNUM, -0.1, -GROUP_INFINITE_BIGNUM),
      Point(GROUP_INFINITE_BIGNUM, 0.1, GROUP_INFINITE_BIGNUM));
}
