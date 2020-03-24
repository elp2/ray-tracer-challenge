#include "display/canvas.h"

#include <cassert>
#include <cstdlib>

Canvas::Canvas(int w, int h) {
  w_ = w;
  h_ = h;
  pixels_ = (Color *)calloc(sizeof(Color), w * h);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      WritePixel(Color(0, 0, 0), x, y);
    }
  }
}

int Canvas::PixelIndex(int x, int y) {
  assert(x >= 0);
  assert(x < w_);
  assert(y >= 0);
  assert(y < h_);

  return x + y * w_;
}

Color Canvas::PixelAt(int x, int y) {
  return pixels_[PixelIndex(x, y)];
}

void Canvas::WritePixel(Color c, int x, int y) {
  pixels_[PixelIndex(x, y)] = c;
}
