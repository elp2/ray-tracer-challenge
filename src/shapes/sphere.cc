#include "shapes/sphere.h"

#include "primitives/intersection.h"

#include <math.h>

Sphere::Sphere() {
  origin_ = TupleFromPoint(0, 0, 0);
}

Intersections Sphere::Intersect(Ray original_ray) {
  Ray ray = original_ray.Transform(transform_.Inverse());

  Tuple sphere_to_ray = ray.Origin() - origin_;
  float a = ray.Direction().Dot(ray.Direction());
  float b = 2 * ray.Direction().Dot(sphere_to_ray);
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
  intersections.push_back(t1);
  intersections.push_back(t2);

  return Intersections(intersections);
}

Tuple Sphere::Normal(Tuple p) {
  return (p - TupleFromPoint(0, 0, 0)).Normalized();
}
