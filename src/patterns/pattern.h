#ifndef RTC_PATTERNS_PATTERN_H
#define RTC_PATTERNS_PATTERN_H

#include "primitives/matrix.h"

class Color;
class Tuple;

class Pattern {
 public:
  ~Pattern() = default;

  const Color ColorAt(const Tuple &object_point) const;

  Matrix transform() const { return transform_; };
  void set_transform(const Matrix transform) { transform_ = transform; };

 protected:
  virtual const Color PatternColorAt(const Tuple &pattern_point) const = 0;

  Matrix transform_ = IdentityMatrix(4);
};

#endif    // RTC_PATTERNS_PATTERN_H
