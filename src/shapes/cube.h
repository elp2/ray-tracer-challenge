#ifndef RTC_SHAPES_CUBE_H
#define RTC_SHAPES_CUBE_H

#include "shapes/shape.h"

#include <vector>

class Ray;
class Tuple;

class Cube : public Shape {
 public:
  Cube();
  ~Cube() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const;

  bool operator==(const Cube o) const;

  const Bounds UnitBounds() const;

 private:
  void CheckAxis(const float &origin, const float &direction, float *tmin, float *tmax) const;
};

#endif    // RTC_SHAPES_CUBE_H
