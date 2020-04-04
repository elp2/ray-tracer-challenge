#ifndef RTC_SHAPES_SPHERE_H
#define RTC_SHAPES_SPHERE_H

#include "primitives/intersections.h"
#include "primitives/matrix.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"
#include "shapes/material.h"
#include "shapes/shape.h"

#include <vector>

class Sphere : public Shape {
 public:
  Sphere();
  ~Sphere() = default;

  Intersections ObjectIntersect(Ray object_ray) const;
  Tuple ObjectNormal(Tuple p);

  bool operator==(const Sphere o) const;

  Tuple origin() const { return origin_; };

 private:
  Tuple origin_;
};

#endif    // RTC_SHAPES_SPHERE_H
