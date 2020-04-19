#ifndef RTC_SHAPES_SMOOTH_TRIANGLE_H
#define RTC_SHAPES_SMOOTH_TRIANGLE_H

#include "shapes/shape.h"

class Ray;
class Tuple;

class SmoothTriangle : public Shape {
 public:
  SmoothTriangle(Tuple p1, Tuple p2, Tuple p3, Tuple n1, Tuple n2, Tuple n3);
  ~SmoothTriangle() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple p) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const;

  bool operator==(const SmoothTriangle o) const;

  const Bounds UnitBounds() const;

  const Tuple p1() const { return p1_; };
  const Tuple p2() const { return p2_; };
  const Tuple p3() const { return p3_; };

  const Tuple n1() const { return n1_; };
  const Tuple n2() const { return n2_; };
  const Tuple n3() const { return n3_; };

  const Tuple e1() const { return p2_ - p1_; };
  const Tuple e2() const { return p3_ - p1_; };

 private:
  Tuple p1_;
  Tuple p2_;
  Tuple p3_;

  Tuple n1_;
  Tuple n2_;
  Tuple n3_;
};

#endif    // RTC_SHAPES_SMOOTH_TRIANGLE_H
