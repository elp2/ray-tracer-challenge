#ifndef RTC_PRIMITIVES_RAY_H
#define RTC_PRIMITIVES_RAY_H

#include "primitives/tuple.h"

class Matrix;

class Ray {
 public:
  Ray();
  Ray(Tuple origin, Tuple direction);
  ~Ray() = default;

  Tuple Origin() const { return origin_; };
  Tuple Direction() const { return direction_; };
  Tuple Position(float t) const;

  const Ray Transform(const Matrix m) const;

  bool operator==(const Ray r) const;
 private:
  Tuple origin_, direction_;
};

#endif    // RTC_PRIMITIVES_RAY_H
