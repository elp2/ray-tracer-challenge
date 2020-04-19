#ifndef RTC_SHAPES_TRIANGLE_H
#define RTC_SHAPES_TRIANGLE_H

#include "shapes/shape.h"

class Ray;
class Tuple;

class Triangle : public Shape {
 public:
  Triangle(Tuple p1, Tuple p2, Tuple p3);
  ~Triangle() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const { return precalculated_normal_; };

  bool operator==(const Triangle o) const;

  const Bounds UnitBounds() const;

  const Tuple p1() const { return p1_; };
  const Tuple p2() const { return p2_; };
  const Tuple p3() const { return p3_; };

  const Tuple e1() const { return p2_ - p1_; };
  const Tuple e2() const { return p3_ - p1_; };

  const Tuple precalculated_normal() const { return precalculated_normal_; };

 private:
  Tuple p1_;
  Tuple p2_;
  Tuple p3_;
  Tuple precalculated_normal_;
};

#endif    // RTC_SHAPES_TRIANGLE_H
