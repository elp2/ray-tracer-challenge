#include "shapes/sphere.h"

#include "primitives/intersection.h"

#include <math.h>

Sphere::Sphere() {
  origin_ = Point(0, 0, 0);
}

Intersections Sphere::ObjectIntersect(Ray object_ray) const {
  Tuple sphere_to_ray = object_ray.Origin() - origin_;
  float a = object_ray.Direction().Dot(object_ray.Direction());
  float b = 2 * object_ray.Direction().Dot(sphere_to_ray);
  float c = sphere_to_ray.Dot(sphere_to_ray) - 1;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return Intersections(std::vector<Intersection>{});
  }

  float two_a = 2 * a;
  float sqrt_discriminant = sqrt(discriminant);

  Intersection t1 = Intersection((-b - sqrt_discriminant) / two_a, this);
  Intersection t2 = Intersection((-b + sqrt_discriminant) / two_a, this);

  std::vector<Intersection> intersections;
  if (t1.T() > t2.T()) {
    intersections.push_back(t2);
    intersections.push_back(t1);
  } else {
    intersections.push_back(t1);
    intersections.push_back(t2);
  }

  return Intersections(intersections);
}

Tuple Sphere::ObjectNormal(Tuple object_point) {
  return object_point - Point(0.0, 0.0, 0.0);
}

bool Sphere::operator==(const Sphere o) const {
  return Shape::operator==(&o) && o.origin() == origin_;
}
