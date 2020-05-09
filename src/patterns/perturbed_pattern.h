#ifndef RTC_PATTERNS_PERTURBED_PATTERN_H
#define RTC_PATTERNS_PERTURBED_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <vector>

class PerturbedPattern : public Pattern {
 public:
  PerturbedPattern(Pattern *pattern);
  ~PerturbedPattern() = default;

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  const Tuple PerturbedPoint(const Tuple &pattern_point) const;
  float PerlinValue(const Tuple &point) const;
  float DotPattern(const int &corner_index, Tuple &point) const ;

  Pattern *pattern_;
  std::vector<Tuple> gradients_;
};

#endif    // RTC_PATTERNS_PERTURBED_PATTERN_H
