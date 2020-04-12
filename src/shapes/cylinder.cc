#include "shapes/cylinder.h"

#include "primitives/intersection.h"
#include "primitives/math.h"
#include "primitives/ray.h"

#include <math.h>

Cylinder::Cylinder() {
}

const Intersections Cylinder::ObjectIntersect(const Ray object_ray) const {
  float a = pow(object_ray.Direction().x(), 2.0) + pow(object_ray.Direction().z(), 2.0);

  if (fabs(a) < EPSILON) {
    // Ray is parallel to y axis so could not intersect.
    return Intersections(std::vector<Intersection> {});
  }

  float b = 2 * object_ray.Origin().x() * object_ray.Direction().x() +
      2 * object_ray.Origin().z() * object_ray.Direction().z();
  float c = pow(object_ray.Origin().x(), 2.0)
      + pow(object_ray.Origin().z(), 2.0) - 1.0;
  float discriminant = pow(b, 2.0) - 4.0 * a * c;
  if (discriminant < 0) {
    // No solution, no intersections.
    return Intersections(std::vector<Intersection> {});
  }
  float sqrt_disc = sqrt(discriminant);
  float t0 = (-b - sqrt_disc) / (2.0 * a);
  float t1 = (-b + sqrt_disc) / (2.0 * a);

  return Intersections(std::vector<Intersection> {
    Intersection(t0, this),
    Intersection(t1, this),
  });
}

const Tuple Cylinder::ObjectNormal(const Tuple object_point) const {
  return Vector(object_point.x(), 0, object_point.z());
}

bool Cylinder::operator==(const Cylinder o) const {
  return Shape::operator==(o);
}
