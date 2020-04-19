#ifndef RTC_SHAPES_CONSTRUCTIVE_SOLID_GEOMETRY_H
#define RTC_SHAPES_CONSTRUCTIVE_SOLID_GEOMETRY_H

#include "shapes/shape.h"

#include <vector>

class Ray;
class Shape;
class Tuple;

class IntersectionStrategy {
 public:
  ~IntersectionStrategy() = default;

  virtual const bool IntersectionAllowed(bool left_hit, bool in_left, bool in_right) const = 0;
};

class UnionIntersectionStrategy : public IntersectionStrategy {
 public:
  UnionIntersectionStrategy() {};
  ~UnionIntersectionStrategy() = default;

  const bool IntersectionAllowed(bool left_hit, bool in_left, bool in_right) const {
    return (left_hit && !in_right) || (!left_hit && !in_left);
  }
};

class IntersectIntersectionStrategy : public IntersectionStrategy {
 public:
  IntersectIntersectionStrategy() {};
  ~IntersectIntersectionStrategy() = default;

  const bool IntersectionAllowed(bool left_hit, bool in_left, bool in_right) const {
    return (left_hit && in_right) || (!left_hit && in_left);
  }
};

class DifferenceIntersectionStrategy : public IntersectionStrategy {
 public:
  DifferenceIntersectionStrategy() {};
  ~DifferenceIntersectionStrategy() = default;

  const bool IntersectionAllowed(bool left_hit, bool in_left, bool in_right) const {
    return (left_hit && !in_right) || (!left_hit && in_left);
  }
};

class ConstructiveSolidGeometry : public Shape {
 public:
  ConstructiveSolidGeometry(Shape *left, Shape *right,
      IntersectionStrategy *intersection_strategy);
  ~ConstructiveSolidGeometry() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const;

  const Intersections FilterIntersections(Intersections &xs) const;

  bool operator==(const ConstructiveSolidGeometry o) const;

  const Bounds UnitBounds() const;

  const bool Includes(Shape *other);

  Shape *left() { return left_; };
  Shape *right() { return right_; };

 private:
  Shape *left_;
  Shape *right_;
  IntersectionStrategy *intersection_strategy_;
};

#endif    // RTC_SHAPES_CONSTRUCTIVE_SOLID_GEOMETRY_H
