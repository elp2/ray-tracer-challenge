#include "patterns/striped_pattern.h"

#include <math.h>

StripedPattern::StripedPattern(Color a, Color b) {
  color_a_ = a;
  color_b_ = b;
}

const Color StripedPattern::ColorAt(const Tuple &object_point) const {
  Tuple pattern_point = transform_.Inverse() * object_point;

  if ((int)floor(pattern_point.x()) % 2 == 0) {
    return color_a_;
  } else {
    return color_b_;
  }
}
