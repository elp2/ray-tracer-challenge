#include "shapes/cube.h"

#include "primitives/intersection.h"
#include "primitives/math.h"

#include <algorithm>
#include <math.h>
#include <utility>

Cube::Cube() {
}

const Intersections Cube::ObjectIntersect(const Ray object_ray) const {
  float xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;

  CheckAxis(object_ray.Origin().x(), object_ray.Direction().x(), &xtmin, &xtmax);
  CheckAxis(object_ray.Origin().y(), object_ray.Direction().y(), &ytmin, &ytmax);
  CheckAxis(object_ray.Origin().z(), object_ray.Direction().z(), &ztmin, &ztmax);

  float tmin = std::fmax(xtmin, std::fmax(ytmin, ztmin));
  float tmax = std::fmin(xtmax, std::fmin(ytmax, ztmax));

  if (tmin > tmax) {
    return Intersections(std::vector<Intersection> {});
  }

  return Intersections(std::vector<Intersection>{
    Intersection(tmin, this),
    Intersection(tmax, this),
  });
}

const Tuple Cube::ObjectNormal(const Tuple object_point) const {
  float max_component = std::fmax(fabs(object_point.x()),
    std::fmax(fabs(object_point.y()), fabs(object_point.z())));
  if (max_component == fabs(object_point.x())) {
    return Vector(object_point.x(), 0, 0);
  } else if (max_component == fabs(object_point.y())) {
    return Vector(0, object_point.y(), 0);
  }
  return Vector(0, 0, object_point.z());
}

bool Cube::operator==(const Cube o) const {
  return Shape::operator==(o);
}

const void Cube::CheckAxis(const float &origin, const float &direction, float *tmin, float *tmax) const {
  float tmin_numerator = (-1.0 - origin);
  float tmax_numerator = (1.0 - origin);

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

const Bounds Cube::UnitBounds() const {
  return Bounds(Point(-1, -1, -1), Point(1, 1, 1));
}
