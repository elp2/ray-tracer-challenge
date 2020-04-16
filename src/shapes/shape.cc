#include "shapes/shape.h"

#include "primitives/intersection.h"
#include "patterns/pattern.h"

#include <math.h>

Intersections Shape::Intersect(const Ray r) const {
  Ray object_ray = r.Transform(transform_.Inverse());
  return ObjectIntersect(object_ray);
}

const Tuple Shape::Normal(const Tuple world_point) const {
  Tuple object_point = WorldPointToObject(world_point);
  Tuple object_normal = ObjectNormal(object_point);
  return ObjectNormalToWorld(object_normal);
}

Color Shape::PatternAt(const Tuple& world_point) const {
  Tuple object_point = WorldPointToObject(world_point);
  return material_.pattern()->ColorAt(object_point);
}

bool Shape::operator==(const Shape &o) const {
  return o.material() == material_ && o.Transform() == transform_;
}

const Tuple Shape::WorldPointToObject(const Tuple &world_point) const {
  Tuple point = world_point;
  if (parent_ != nullptr) {
    point = parent_->WorldPointToObject(world_point);
  }
  return transform_.Inverse() * point;
}

const Tuple Shape::ObjectNormalToWorld(const Tuple &normal_vector) const {
  Tuple vector = transform_.Inverse().Transpose() * normal_vector;
  vector.SetW(0);
  vector = vector.Normalized();

  if (parent_ != nullptr) {
    vector = parent_->ObjectNormalToWorld(vector);
  }

  return vector;
}

const Color Shape::Lighting(PointLight light, Tuple position, Tuple eye_vector,
    Tuple normal_vector, bool in_shadow) const {
  return material_.Lighting(light, position, eye_vector, normal_vector, in_shadow, this);
}
