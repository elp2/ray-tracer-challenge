#include "patterns/pattern.h"

#include "primitives/color.h"
#include "primitives/tuple.h"

const Color Pattern::ColorAt(const Tuple &object_point) const {
  Tuple pattern_point = transform_.Inverse() * object_point;
  return PatternColorAt(pattern_point);
}
