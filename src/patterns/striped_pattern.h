#ifndef RTC_PATTERNS_STRIPED_PATTERN_H
#define RTC_PATTERNS_STRIPED_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"

class Tuple;

class StripedPattern : public Pattern {
 public:
  StripedPattern(Color a, Color b);
  ~StripedPattern() = default;

  const Color ColorAt(const Tuple &object_point) const;

  const Color color_a() const { return color_a_; };
  const Color color_b() const { return color_b_; };
 private:
  Color color_a_, color_b_;
};

#endif    // RTC_PATTERNS_STRIPED_PATTERN_H
