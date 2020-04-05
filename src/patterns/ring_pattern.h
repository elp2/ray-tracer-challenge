#ifndef RTC_PATTERNS_RING_PATTERN_H
#define RTC_PATTERNS_RING_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"

class Tuple;

class RingPattern : public Pattern {
 public:
  RingPattern(Color a, Color b);
  ~RingPattern() = default;

  const Color color_a() const { return color_a_; };
  const Color color_b() const { return color_b_; };

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  Color color_a_, color_b_;
};

#endif    // RTC_PATTERNS_RING_PATTERN_H
