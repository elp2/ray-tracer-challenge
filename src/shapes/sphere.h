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

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple p) const;

  bool operator==(const Sphere o) const;

  const Tuple origin() const { return origin_; };

 private:
  Tuple origin_;
};

Sphere *GlassySphere();

#endif    // RTC_SHAPES_SPHERE_H
