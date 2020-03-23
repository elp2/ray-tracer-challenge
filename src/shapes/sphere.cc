#include "shapes/sphere.h"

#include "primitives/intersection.h"

#include <math.h>

Sphere::Sphere() {
  origin_ = TupleFromPoint(0, 0, 0);
  radius_ = 1.0;
}

std::vector<Intersection> Sphere::Intersections(Ray ray) {
  std::vector<Intersection> intersections;

  Tuple sphere_to_ray = ray.Origin() - origin_;
  float a = ray.Direction().Dot(ray.Direction());
  float b = 2 * ray.Direction().Dot(sphere_to_ray);
  float c = sphere_to_ray.Dot(sphere_to_ray) - 1;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return intersections;
  }

  float two_a = 2 * a;
  float sqrt_discriminant = sqrt(discriminant);
  Intersection t1 = Intersection((-b - sqrt_discriminant) / two_a);
  Intersection t2 = Intersection((-b + sqrt_discriminant) / two_a);
  intersections.push_back(t1);
  intersections.push_back(t2);

  return intersections;
}
