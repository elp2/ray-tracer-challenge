#ifndef RTC_PATTERNS_PATTERN_H
#define RTC_PATTERNS_PATTERN_H

class Color;
class Tuple;

class Pattern {
 public:
  ~Pattern() = default;

  virtual const Color ColorAt(const Tuple &p) const;
};

#endif    // RTC_PATTERNS_PATTERN_H
