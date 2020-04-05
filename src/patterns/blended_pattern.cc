#include "patterns/blended_pattern.h"

BlendedPattern::BlendedPattern(Pattern *pattern_a, Pattern *pattern_b) {
  pattern_a_ = pattern_a; 
  pattern_b_ = pattern_b;
}

const Color BlendedPattern::PatternColorAt(const Tuple &pattern_point) const {
  Color a = pattern_a_->ColorAt(pattern_point);
  Color b = pattern_b_->ColorAt(pattern_point);

  return a.Blend(b);
}
