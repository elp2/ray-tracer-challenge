#ifndef RTC_SHAPES_SPHERE_H
#define RTC_SHAPES_SPHERE_H

#include "primitives/intersection.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"

#include <vector>

class Sphere {
 public:
  Sphere();
  ~Sphere() = default;

  std::vector<Intersection> Intersections(Ray r);

 private:
  Tuple origin_;
  float radius_;
};

#endif    // RTC_SHAPES_SPHERE_H
