#include "patterns/three_d_pattern.h"

#include <math.h>

ThreeDPattern::ThreeDPattern(Color a, Color b) {
  color_a_ = a;
  color_b_ = b;
}

const Color ThreeDPattern::PatternColorAt(const Tuple &pattern_point) const {
  int floored_distance = (int)floor(pattern_point.x()) + (int)floor(pattern_point.y())
    + (int)floor(pattern_point.z());
  if (floored_distance % 2 == 0) {
    return color_a_;
  } else { 
    return color_b_;
  }
}
