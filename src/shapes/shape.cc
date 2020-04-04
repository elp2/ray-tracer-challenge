#include "shapes/shape.h"

#include "primitives/intersection.h"
#include "patterns/pattern.h"

#include <math.h>

Intersections Shape::Intersect(const Ray r) const {
  Ray object_ray = r.Transform(transform_.Inverse());
  return ObjectIntersect(object_ray);
}

const Tuple Shape::Normal(const Tuple world_point) const {
  Tuple object_point = transform_.Inverse() * world_point;
  Tuple object_normal = ObjectNormal(object_point);
  Tuple world_normal = transform_.Inverse().Transpose() * object_normal;
  world_normal.SetW(0.0);
  return world_normal.Normalized();
}

Color Shape::PatternAt(const Tuple& world_point) const {
  Tuple object_point = transform_.Inverse() * world_point;
  return material_.pattern()->ColorAt(object_point);
}

bool Shape::operator==(const Shape &o) const {
  return o.material() == material_ && o.Transform() == transform_;
}
