#ifndef RTC_PATTERNS_TEXTURE_PATTERN_H
#define RTC_PATTERNS_TEXTURE_PATTERN_H

#include "patterns/pattern.h"
#include "primitives/color.h"

#include <vector>

class Tuple;

class TexturePattern : public Pattern {
 public:
  TexturePattern(int w, int h, std::vector<Color> *texture, bool interpolate);
  ~TexturePattern() = default;

 protected:
  const Color PatternColorAt(const Tuple &pattern_point) const;

 private:
  int w_;
  int h_;
  bool interpolate_;
  std::vector<Color> *texture_;

  const Color InterpolatedColor(float x, float y) const;
  Color TextureColorAt(float xf, float yf) const;
};

#endif    // RTC_PATTERNS_TEXTURE_PATTERN_H
