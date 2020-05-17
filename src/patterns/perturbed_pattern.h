#ifndef RTC_PATTERNS_PERTURBED_PATTERN_H
#define RTC_PATTERNS_PERTURBED_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <vector>

class PerlinNoise;

class PerturbedPattern : public Pattern {
 public:
  PerturbedPattern(Pattern *pattern);
  ~PerturbedPattern() = default;

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  const Tuple PerturbedPoint(const Tuple &pattern_point) const;
  Pattern *pattern_;
  PerlinNoise *noise_;
};

#endif    // RTC_PATTERNS_PERTURBED_PATTERN_H
