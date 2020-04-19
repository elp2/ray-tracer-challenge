#ifndef RTC_SHAPES_CONE_H
#define RTC_SHAPES_CONE_H

#include "shapes/shape.h"

#include <math.h>

class Ray;
class Tuple;

class Cone : public Shape {
 public:
  Cone();
  Cone(float maximum, float minimum, bool closed);

  ~Cone() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const;

  bool operator==(const Cone o) const;

  const float maximum() const { return maximum_; };
  const float minimum() const { return minimum_; };
  const bool closed() const { return closed_; };

  const Bounds UnitBounds() const;

 private:
  float maximum_ = INFINITY;
  float minimum_ = -INFINITY;
  bool closed_ = false;

  const bool IntersectsCap(const Ray &r, const float &t, const float &cap_radius) const;
  const void CapIntersections(const Ray &r, std::vector<Intersection> *xs) const;
};

#endif    // RTC_SHAPES_CONE_H
