#include "patterns/gradient_pattern.h"

#include <math.h>

GradientPattern::GradientPattern(Color a, Color b) {
  color_a_ = a;
  color_b_ = b;
}

const Color GradientPattern::PatternColorAt(const Tuple &pattern_point) const {
  Color step = color_b_ - color_a_;
  float fraction = pattern_point.x() - floor(pattern_point.x());

  return color_a_ + step * fraction;
}
