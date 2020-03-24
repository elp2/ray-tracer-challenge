#ifndef RTC_PRIMITIVES_RAY_H
#define RTC_PRIMITIVES_RAY_H

#include "primitives/tuple.h"

class Matrix;

class Ray {
 public:
  Ray(Tuple origin, Tuple direction);
  ~Ray() = default;

  Tuple Origin() { return origin_; };
  Tuple Direction() { return direction_; };
  Tuple Position(float t);

  Ray Transform(Matrix m);

 private:
  Tuple origin_, direction_;
};

#endif    // RTC_PRIMITIVES_RAY_H
