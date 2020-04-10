#ifndef RTC_SCENE_PREPARED_COMPUTATION_H
#define RTC_SCENE_PREPARED_COMPUTATION_H

class Intersection;
class Intersections;
class Ray;
class Shape;

#include "primitives/tuple.h"

class PreparedComputation {
 public:
  PreparedComputation(Intersection hit, Ray &r, Intersections &xs);
  ~PreparedComputation() = default;

  float t() { return t_; };
  const Shape *object() { return object_; };
  Tuple point() const { return point_; };
  Tuple over_point() const { return over_point_; };
  Tuple under_point() const { return under_point_; };
  Tuple eye_vector() const { return eye_vector_; };
  Tuple normal_vector() const { return normal_vector_; };
  Tuple reflect_vector() const { return reflect_vector_; };
  bool inside() const { return inside_; };
  float n1() const { return n1_; };
  float n2() const { return n2_; };
  float schlick();

 private:
  float t_;
  const Shape *object_;
  Tuple point_;
  // Slightly up the normal from point_.
  Tuple over_point_;
  // Slightly under the normal from point_.
  Tuple under_point_;
  Tuple eye_vector_;
  Tuple normal_vector_;
  Tuple reflect_vector_;
  bool inside_;
  float n1_;
  float n2_;
  void CalculateN1N2(Intersections &xs, Intersection &hit);
};

#endif    // RTC_SCENE_PREPARED_COMPUTATION_H
