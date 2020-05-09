#ifndef RTC_SHAPES_CYLINDER_H
#define RTC_SHAPES_CYLINDER_H

#include "shapes/shape.h"

#include <math.h>
#include <vector>

class Ray;
class Tuple;

class Cylinder : public Shape {
 public:
  Cylinder();
  Cylinder(float maximum, float minimum, bool closed);

  ~Cylinder() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const;

  bool operator==(const Cylinder o) const;

  float maximum() const { return maximum_; };
  float minimum() const { return minimum_; };
  bool closed() const { return closed_; };

  const Bounds UnitBounds() const;

 private:
  float maximum_ = INFINITY;
  float minimum_ = -INFINITY;
  bool closed_ = false;

  bool IntersectsCap(const Ray &r, const float &t) const;
  void CapIntersections(const Ray &r, std::vector<Intersection> *xs) const;
};

#endif    // RTC_SHAPES_CYLINDER_H
