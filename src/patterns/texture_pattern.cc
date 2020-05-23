#include "patterns/texture_pattern.h"

#include <math.h>

TexturePattern::TexturePattern(int w, int h, std::vector<Color> *texture) {
  w_ = w;
  h_ = h;
  texture_ = texture;
}

const Color TexturePattern::PatternColorAt(const Tuple &pattern_point) const {
  // This is really planar mapping.

  float x = pattern_point.x() * (float) w_;
  float z = pattern_point.z() * (float) h_;

  return InterpolatedColor(x, z);
}

const Color TexturePattern::InterpolatedColor(float x, float y) const {
  float xdecimal = x - floor(x);
  float ydecimal = y - floor(y);

  float rw = fabs(0.5 - xdecimal);
  float rh = fabs(0.5 - ydecimal);

  int dx = (xdecimal > 0.5) ? 1 : -1;
  int dy = (ydecimal > 0.5) ? 1 : -1;

  Color color = TextureColorAt(x, y) * ((1 - rw) * (1 - rh));
  // TODO add operator +=.
  color = color + TextureColorAt(x + dx, y) * (rw * (1 - rh));
  color = color + TextureColorAt(x, y + dy) * ((1- rw) * rh);
  color = color + TextureColorAt(x + dx, y + dy) * (rw * rh);

  return color;
}

Color TexturePattern::TextureColorAt(float xf, float yf) const {
  int x = (int)roundf(xf / w_) % w_;
  int y = (int)roundf(yf - h_) % h_;

  return (*texture_)[x + y * w_];
}
