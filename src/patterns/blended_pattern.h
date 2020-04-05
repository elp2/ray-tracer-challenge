#ifndef RTC_PATTERNS_BLENDED_PATTERN_H
#define RTC_PATTERNS_BLENDED_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <vector>

class BlendedPattern : public Pattern {
 public:
  BlendedPattern(Pattern *pattern_a, Pattern *pattern_b);
  ~BlendedPattern() = default;

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  Pattern *pattern_a_, *pattern_b_;
};

#endif    // RTC_PATTERNS_BLENDED_PATTERN_H
