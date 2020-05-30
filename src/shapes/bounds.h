#ifndef RTC_SHAPES_BOUNDS_H
#define RTC_SHAPES_BOUNDS_H

#include "primitives/matrix.h"
#include "primitives/tuple.h"

#include <vector>

class Bounds {
 public:
  Bounds(Tuple minimum, Tuple maximum);
  ~Bounds() = default;

  void ExtendToFit(const Tuple &point);
  void MergeWith(const Bounds &other);

  const Tuple minimum() const { return minimum_; };
  const Tuple maximum() const { return maximum_; };
  const Tuple center() const;

  // Returns a transformation matrix that will make certain axes
  // span -1..1.
  const Matrix UnitifyTransform(bool unitify_x, bool unitify_y, bool unitify_z) const;

 protected:
  Tuple minimum_;
  Tuple maximum_;
};

#endif    // RTC_SHAPES_BOUNDS_H