#ifndef RTC_SHAPES_SPHERE_H
#define RTC_SHAPES_SPHERE_H

#include "primitives/intersections.h"
#include "primitives/matrix.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"
#include "shapes/material.h"

#include <vector>

class Sphere {
 public:
  Sphere();
  ~Sphere() = default;

  Intersections Intersect(Ray r);

  void SetTransform(Matrix m) { transform_ = m; };
  Matrix Transform() { return transform_; };
  Tuple Normal(Tuple p);

  void set_material(Material material) { material_ = material; };
  Material material() { return material_; };

 private:
  Tuple origin_;
  Matrix transform_ = IdentityMatrix(4);
  Material material_ = Material();
};

#endif    // RTC_SHAPES_SPHERE_H
