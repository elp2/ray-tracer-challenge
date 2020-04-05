#ifndef RTC_PATTERNS_THREE_D_PATTERN_H
#define RTC_PATTERNS_THREE_D_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"

class Tuple;

class ThreeDPattern : public Pattern {
 public:
  ThreeDPattern(Color a, Color b);
  ~ThreeDPattern() = default;

  const Color color_a() const { return color_a_; };
  const Color color_b() const { return color_b_; };

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  Color color_a_, color_b_;
};

#endif    // RTC_PATTERNS_THREE_D_PATTERN_H
