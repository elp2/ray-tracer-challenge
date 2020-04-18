#include "shapes/cone.h"

#include "primitives/intersection.h"
#include "primitives/math.h"
#include "primitives/ray.h"
#include "shapes/bounds.h"

#include <cassert>
#include <math.h>

Cone::Cone() {
}

Cone::Cone(float maximum, float minimum, bool closed) {
  maximum_ = maximum;
  minimum_ = minimum;
  closed_ = closed;

  assert(maximum_ > minimum_);
}

// TODO: Lots of acne on cones. See chapter13.cc demo.
const Intersections Cone::ObjectIntersect(const Ray object_ray) const {
  float a = pow(object_ray.Direction().x(), 2.0)
      - pow(object_ray.Direction().y(), 2.0)
      + pow(object_ray.Direction().z(), 2.0);

  float b = 2 * object_ray.Origin().x() * object_ray.Direction().x()
      - 2 * object_ray.Origin().y() * object_ray.Direction().y()
      + 2 * object_ray.Origin().z() * object_ray.Direction().z();

  float c = pow(object_ray.Origin().x(), 2.0)
      - pow(object_ray.Origin().y(), 2.0)
      + pow(object_ray.Origin().z(), 2.0);

  std::vector<Intersection> xs;
  if (fabs(a) < EPSILON && fabs(b) > EPSILON) {
    float t = -c / (2.0 * b);
    xs.push_back(Intersection(t, this));
    CapIntersections(object_ray, &xs);
    return xs;
  }
  if (fabs(a) < EPSILON) {
    return std::vector<Intersection>({});
  }

  float discriminant = pow(b, 2.0) - 4.0 * a * c;
  if (fabs(discriminant) < EPSILON) {
    discriminant = 0;
  }
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

const Tuple Cone::ObjectNormal(const Tuple object_point) const {
  float y = sqrt(pow(object_point.x(), 2.0) + pow(object_point.z(), 2.0));
  if (object_point.y() > 0) {
    y = -y;
  }
  if (y <= 1 && object_point.y() >= maximum_ - EPSILON) {
    return Vector(0, 1, 0);
  }
  if (y <= 1 && object_point.y() <= minimum_ + EPSILON) {
    return Vector(0, -1, 0);
  }
  return Vector(object_point.x(), y, object_point.z());
}

bool Cone::operator==(const Cone o) const {
  return Shape::operator==(o);
}

const bool Cone::IntersectsCap(const Ray &r, const float &t, const float &cap_radius) const {
  float x = r.Origin().x() + t * r.Direction().x();
  float z = r.Origin().z() + t * r.Direction().z();

  return (pow(x, 2) + pow(z, 2)) <= cap_radius + EPSILON;
}

const void Cone::CapIntersections(const Ray &r, std::vector<Intersection> *xs) const {
  if (!closed_ || fabs(r.Direction().y()) < EPSILON) {
    return;
  }

  float t = (minimum_ - r.Origin().y()) / r.Direction().y();
  if (IntersectsCap(r, t, fabs(minimum_))) {
    xs->push_back(Intersection(t, this));
  }
  t = (maximum_ - r.Origin().y()) / r.Direction().y();
  if (IntersectsCap(r, t, fabs(maximum_))) {
    xs->push_back(Intersection(t, this));
  }
}

const Bounds Cone::UnitBounds() const {
  float xmax = INFINITY;
  float ymax = INFINITY;
  float zmax = INFINITY;
  if (maximum_ != INFINITY) {
    xmax = ymax = zmax = maximum_;
  }

  float xmin = -INFINITY;
  float ymin = -INFINITY;
  float zmin = -INFINITY;
  if (minimum_ != -INFINITY) {
    xmin = ymin = zmin = minimum_;
  }

  return Bounds(Point(xmin, ymin, zmin), Point(xmax, ymax, zmax));
}
