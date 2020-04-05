#include "patterns/ring_pattern.h"

#include <math.h>

RingPattern::RingPattern(Color a, Color b) {
  color_a_ = a;
  color_b_ = b;
}

const Color RingPattern::PatternColorAt(const Tuple &pattern_point) const {
  float origin_distance = (pattern_point - Point(0, 0, 0)).Magnitude();
  if ((int)floor(origin_distance) % 2 == 0) {
    return color_a_;
  } else { 
    return color_b_;
  }
}
