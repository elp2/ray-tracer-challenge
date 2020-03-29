#ifndef RTC_SCENE_PREPARED_COMPUTATION_H
#define RTC_SCENE_PREPARED_COMPUTATION_H

class Intersection;
class Ray;

#include "primitives/tuple.h"

class PreparedComputation {
 public:
  PreparedComputation(Intersection i, Ray r);
  ~PreparedComputation() = default;

  float t() { return t_; };
  const void *object() { return object_; };
  Tuple point() const { return point_; };
  Tuple eye_vector() const { return eye_vector_; };
  Tuple normal_vector() const { return normal_vector_; };
  bool inside() const { return inside_; };

 private:
  float t_;
  const void *object_;
  Tuple point_;
  Tuple eye_vector_;
  Tuple normal_vector_;
  bool inside_;
};

#endif    // RTC_SCENE_PREPARED_COMPUTATION_H
