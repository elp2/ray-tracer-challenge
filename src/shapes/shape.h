#ifndef RTC_SHAPES_SHAPE_H
#define RTC_SHAPES_SHAPE_H

#include "primitives/intersections.h"
#include "primitives/matrix.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"
#include "shapes/bounds.h"
#include "shapes/material.h"

#include <vector>

class PerlinNoise;

class Shape {
 public:
  ~Shape() = default;

  Intersections Intersect(const Ray r) const;
  const Tuple Normal(const Tuple &world_point, const Intersection &i) const;

  void SetTransform(Matrix m) { transform_ = m; };
  Matrix Transform() const { return transform_; };

  void set_material(Material material) { material_ = material; };
  Material material() const { return material_; };

  Color PatternAt(const Tuple& world_point) const;

  bool operator==(const Shape &o) const;

  void set_parent(Shape *parent) { parent_ = parent; };
  const Shape *parent() { return parent_; };

  const Tuple WorldPointToObject(const Tuple &world_point) const;
  const Tuple ObjectNormalToWorld(const Tuple &normal_vector) const;

  const Color Lighting(const Lightlet *lightlet, Tuple position, Tuple eye_vector,
      Tuple normal_vector, float shadowing) const;

  virtual const Bounds UnitBounds() const = 0;

  bool Includes(Shape *other);

  void set_normal_noise(PerlinNoise *normal_noise) { normal_noise_ = normal_noise; };

 protected:
  virtual const Intersections ObjectIntersect(const Ray object_ray) const = 0;
  virtual const Tuple ObjectNormal(const Tuple &p, const Intersection &i) const = 0;
  const Bounds ChildBounds(Shape *child) const;

  Matrix transform_ = IdentityMatrix(4);
  Material material_ = Material();
  Shape *parent_ = nullptr;
  PerlinNoise *normal_noise_ = nullptr;
};

#endif    // RTC_SHAPES_SHAPE_H
