#include "shapes/shape.h"

#include "primitives/intersection.h"
#include "patterns/pattern.h"

#include <math.h>

Intersections Shape::Intersect(const Ray r) const {
  Ray object_ray = r.Transform(transform_.Inverse());
  return ObjectIntersect(object_ray);
}

const Tuple Shape::Normal(const Tuple &world_point, const Intersection &i)  const {
  Tuple object_point = WorldPointToObject(world_point);
  Tuple object_normal = ObjectNormal(object_point, i);
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

const Bounds Shape::ChildBounds(Shape *child) const {
  Bounds unit_bounds = child->UnitBounds();
  float xc = (unit_bounds.maximum().x() + unit_bounds.minimum().x()) / 2.0;
  float yc = (unit_bounds.maximum().y() + unit_bounds.minimum().y()) / 2.0;
  float zc = (unit_bounds.maximum().z() + unit_bounds.minimum().z()) / 2.0;

  float xd = unit_bounds.maximum().x() - xc;
  float yd = unit_bounds.maximum().y() - yc;
  float zd = unit_bounds.maximum().z() - zc;

  Tuple center_point = Point(xc, yc, zc);
  Bounds child_bounds = Bounds(child->Transform() * center_point, child->Transform() * center_point);

  for (float x = -1; x < 2; x += 2) {
    for (float y = -1; y < 2; y += 2) {
      for (float z = -1; z < 2; z += 2) {
        Tuple corner_vector = Vector(x * xd, y * yd, z * zd);
        Tuple corner = center_point + corner_vector;
        Tuple transformed_corner = child->Transform() * corner;
        child_bounds.ExtendToFit(transformed_corner);
      }
    }
  }
  return child_bounds;
}

bool Shape::Includes(Shape *other) {
  return this == other;
}
