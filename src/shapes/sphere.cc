#include "shapes/sphere.h"

#include "primitives/intersection.h"

#include <math.h>

Sphere::Sphere() {
  origin_ = TupleFromPoint(0, 0, 0);
}

Intersections Sphere::Intersect(Ray original_ray) const {
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
  if (t1.T() > t2.T()) {
    intersections.push_back(t2);
    intersections.push_back(t1);
  } else {
    intersections.push_back(t1);
    intersections.push_back(t2);
  }

  return Intersections(intersections);
}

Tuple Sphere::Normal(Tuple world_point) {
  Tuple object_point = transform_.Inverse() * world_point;
  Tuple object_normal = object_point - TupleFromPoint(0.0, 0.0, 0.0);
  Tuple world_normal = transform_.Inverse().Transpose() * object_normal;
  world_normal.SetW(0.0);
  return world_normal.Normalized();
}

bool Sphere::operator==(const Sphere o) const {
  return o.material() == material_ && o.Transform() == transform_ && o.origin() == origin_;
}
