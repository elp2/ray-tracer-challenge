#include "patterns/striped_pattern.h"

#include <math.h>

StripedPattern::StripedPattern(Color a, Color b) {
  color_a_ = a;
  color_b_ = b;
}

const Color StripedPattern::PatternColorAt(const Tuple &pattern_point) const {
  if ((int)floor(pattern_point.x()) % 2 == 0) {
    return color_a_;
  } else {
    return color_b_;
  }
}
