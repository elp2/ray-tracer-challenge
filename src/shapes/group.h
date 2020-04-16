#ifndef RTC_SHAPES_GROUP_H
#define RTC_SHAPES_GROUP_H

#include "primitives/intersections.h"
#include "primitives/matrix.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"
#include "shapes/material.h"
#include "shapes/shape.h"

#include <vector>

class Group : public Shape {
 public:
  Group();
  ~Group() = default;

  const Intersections ObjectIntersect(const Ray object_ray) const;
  const Tuple ObjectNormal(const Tuple p) const;

  bool operator==(const Group o) const;

  const int size() const { return children_->size(); };

  void AddChild(Shape * child);
  const std::vector<Shape *> *children() const { return children_; };

 private:
  std::vector<Shape *> *children_;
};

#endif    // RTC_SHAPES_GROUP_H
