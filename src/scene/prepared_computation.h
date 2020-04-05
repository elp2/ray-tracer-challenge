#ifndef RTC_SCENE_PREPARED_COMPUTATION_H
#define RTC_SCENE_PREPARED_COMPUTATION_H

class Intersection;
class Ray;
class Shape;

#include "primitives/tuple.h"

class PreparedComputation {
 public:
  PreparedComputation(Intersection i, Ray r);
  ~PreparedComputation() = default;

  float t() { return t_; };
  const Shape *object() { return object_; };
  Tuple point() const { return point_; };
  Tuple over_point() const { return over_point_; };
  Tuple eye_vector() const { return eye_vector_; };
  Tuple normal_vector() const { return normal_vector_; };
  Tuple reflect_vector() const { return reflect_vector_; };
  bool inside() const { return inside_; };

 private:
  float t_;
  const Shape *object_;
  Tuple point_;
  // Slightly up the normal from point_.
  Tuple over_point_;
  Tuple eye_vector_;
  Tuple normal_vector_;
  Tuple reflect_vector_;
  bool inside_;
};

#endif    // RTC_SCENE_PREPARED_COMPUTATION_H
