#include "display/canvas.h"

#include <iostream>

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

Color Canvas::PixelAt(int x, int y) {
  if (x < 0 || y < 0 || x >= w_ || y >= h_) {
    std::cout << "Access beyond canvas boundaries." << std::endl;
  }
  return pixels_[x + y * w_];
}

void Canvas::WritePixel(Color c, int x, int y) {
  pixels_[x + y * w_] = c;
}
