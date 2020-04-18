#include "shapes/triangle.h"

#include "primitives/intersection.h"
#include "primitives/math.h"

#include <algorithm>
#include <math.h>
#include <utility>

Triangle::Triangle(Tuple p1, Tuple p2, Tuple p3) {
  p1_ = p1;
  p2_ = p2;
  p3_ = p3;

  precalculated_normal_ = e2().Cross(e1()).Normalized();
}

const Intersections Triangle::ObjectIntersect(const Ray object_ray) const {
  Tuple dir_cross_e2 = object_ray.Direction().Cross(e2());
  float dot = e1().Dot(dir_cross_e2);
  if (fabs(dot) < EPSILON) {
    return Intersections(std::vector<Intersection> {});
  }

  float f = 1.0 / dot;
  Tuple p1_to_origin = object_ray.Origin() - p1();
  float u = f * p1_to_origin.Dot(dir_cross_e2);
  if (u < EPSILON || u > 1) {
    return Intersections(std::vector<Intersection> {});
  }

  Tuple origin_cross_e1 = p1_to_origin.Cross(e1());
  float v = f * object_ray.Direction().Dot(origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return Intersections(std::vector<Intersection> {});
  }

  float t = f * e2().Dot(origin_cross_e1);
  return Intersections(std::vector<Intersection> {Intersection(t, this)});
}

bool Triangle::operator==(const Triangle o) const {
  return Shape::operator==(o) && o.p1() == p1_ && o.p2() == p2_ && o.p3() == p3_;
}

const Bounds Triangle::UnitBounds() const {
  float minx = std::min(p1_.x(), std::min(p2_.x(), p3_.x()));
  float miny = std::min(p1_.y(), std::min(p2_.y(), p3_.y()));
  float minz = std::min(p1_.z(), std::min(p2_.z(), p3_.z()));

  float maxx = std::max(p1_.x(), std::max(p2_.x(), p3_.x()));
  float maxy = std::max(p1_.y(), std::max(p2_.y(), p3_.y()));
  float maxz = std::max(p1_.z(), std::max(p2_.z(), p3_.z()));

  return Bounds(Point(minx, miny, minz), Point(maxx, maxy, maxz));
}
