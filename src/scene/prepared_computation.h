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

  const float t() const { return t_; };
  const Shape *object() const { return object_; };
  const Tuple point() const { return point_; };
  const Tuple over_point() const { return over_point_; };
  const Tuple under_point() const { return under_point_; };
  const Tuple eye_vector() const { return eye_vector_; };
  const Tuple normal_vector() const { return normal_vector_; };
  const Tuple reflect_vector() const { return reflect_vector_; };
  const bool inside() const { return inside_; };
  const float n1() const { return n1_; };
  const float n2() const { return n2_; };
  const float schlick() const;

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
