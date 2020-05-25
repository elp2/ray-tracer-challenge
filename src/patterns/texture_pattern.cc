#include "patterns/texture_pattern.h"

#include <cassert>
#include <math.h>

TexturePattern::TexturePattern(int w, int h, std::vector<Color> *texture, bool interpolate) {
  w_ = w;
  h_ = h;
  texture_ = texture;
  interpolate_ = interpolate;
}

const Color TexturePattern::PatternColorAt(const Tuple &pattern_point) const {
  // This is really planar mapping.

  float x = pattern_point.x() * (float) w_;
  float z = pattern_point.z() * (float) h_;

  return InterpolatedColor(x, z);
}

const Color TexturePattern::InterpolatedColor(float x, float y) const {
  if (!interpolate_) {
    return TextureColorAt(x, y);
  }
  float xdecimal = x - floor(x);
  float ydecimal = y - floor(y);

  float rw = fabs(0.5 - xdecimal);
  float rh = fabs(0.5 - ydecimal);

  int dx = (xdecimal > 0.5) ? 1 : -1;
  int dy = (ydecimal > 0.5) ? 1 : -1;

  Color c = TextureColorAt(x, y) * ((1 - rw) * (1 - rh));
  // TODO add operator +=.
  Color cdx = TextureColorAt(x + dx, y) * (rw * (1 - rh));
  Color cdy = TextureColorAt(x, y + dy) * ((1- rw) * rh);
  Color cdxdy = TextureColorAt(x + dx, y + dy) * (rw * rh);

  return c+ cdx + cdy + cdxdy;
}

Color TexturePattern::TextureColorAt(float xf, float yf) const {
  int x = (int)floorf(xf) % w_;
  int y = (int)floorf(yf) % h_;
  if (x < 0) {
    x += w_;
  }
  if (y < 0) {
    y += h_;
  }
  assert(x >= 0);
  assert(y >= 0);
  assert(y < h_);
  assert(x < w_);

  Color ret = (*texture_)[x + y * w_];
  return ret;
}
