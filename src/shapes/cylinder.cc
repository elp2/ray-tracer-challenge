#include "shapes/cylinder.h"

#include "primitives/intersection.h"
#include "primitives/math.h"
#include "primitives/ray.h"
#include "shapes/bounds.h"

#include <cassert>
#include <math.h>

Cylinder::Cylinder() {
}

Cylinder::Cylinder(float maximum, float minimum, bool closed) {
  maximum_ = maximum;
  minimum_ = minimum;
  closed_ = closed;

  assert(maximum_ > minimum_);
}

const Intersections Cylinder::ObjectIntersect(const Ray object_ray) const {
  float a = pow(object_ray.Direction().x(), 2.0) + pow(object_ray.Direction().z(), 2.0);
  // If a~= 0 Ray is parallel to y axis so could not intersect.
  // However, we still need to see if a cap could intersect at the end.

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
  if (t0 > t1) {
    std::swap(t0, t1);
  }

  std::vector<Intersection> xs;
  float y0 = object_ray.Origin().y() + t0 * object_ray.Direction().y();
  if (minimum_ < y0 && y0 < maximum_) {
    xs.push_back(Intersection(t0, this));
  }
  float y1 = object_ray.Origin().y() + t1 * object_ray.Direction().y();
  if (minimum_ < y1 && y1 < maximum_) {
    xs.push_back(Intersection(t1, this));
  }

  CapIntersections(object_ray, &xs);
  return Intersections(std::vector<Intersection> { xs });
}

const Tuple Cylinder::ObjectNormal(const Tuple &object_point, const Intersection &i) const {
  float dist = pow(object_point.x(), 2.0) + pow(object_point.z(), 2.0);
  if (dist <= 1 && object_point.y() >= maximum_ - EPSILON) {
    return Vector(0, 1, 0);
  }
  if (dist <= 1 && object_point.y() <= minimum_ + EPSILON) {
    return Vector(0, -1, 0);
  }
  return Vector(object_point.x(), 0, object_point.z());
}

bool Cylinder::operator==(const Cylinder o) const {
  return Shape::operator==(o);
}

bool Cylinder::IntersectsCap(const Ray &r, const float &t) const {
  float x = r.Origin().x() + t * r.Direction().x();
  float z = r.Origin().z() + t * r.Direction().z();

  return (pow(x, 2) + pow(z, 2)) <= 1.0 + EPSILON;
}

void Cylinder::CapIntersections(const Ray &r, std::vector<Intersection> *xs) const {
  if (!closed_ || fabs(r.Direction().y()) < EPSILON) {
    return;
  }

  float t = (minimum_ - r.Origin().y()) / r.Direction().y();
  if (IntersectsCap(r, t)) {
    xs->push_back(Intersection(t, this));
  }
  t = (maximum_ - r.Origin().y()) / r.Direction().y();
  if (IntersectsCap(r, t)) {
    xs->push_back(Intersection(t, this));
  }
}

const Bounds Cylinder::UnitBounds() const {
  float xmax = 1;
  float ymax = INFINITY;
  float zmax = 1;
  if (maximum_ != INFINITY) {
    ymax = maximum_;
  }

  float xmin = -1;
  float ymin = -INFINITY;
  float zmin = -1;
  if (minimum_ != -INFINITY) {
    ymin = minimum_;
  }

  return Bounds(Point(xmin, ymin, zmin), Point(xmax, ymax, zmax));
}
