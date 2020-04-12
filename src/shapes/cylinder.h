#ifndef RTC_SHAPES_CYLINDER
#define RTC_SHAPES_CYLINDER

#include "shapes/shape.h"

#include <vector>

class Ray;
class Tuple;

class Cylinder : public Shape {
 public:
  Cylinder();
  ~Cylinder() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple p) const;

  bool operator==(const Cylinder o) const;
};

#endif    // RTC_SHAPES_CYLINDER
