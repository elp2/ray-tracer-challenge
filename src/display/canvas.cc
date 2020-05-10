#include "display/canvas.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <mutex>

std::mutex mutex_;

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
  std::unique_lock<std::mutex> guard(mutex_);

  if (report_render_progress_) {
    ++rendered_;
    float progress = 100.0 * (float)rendered_ / (float)(w_ * h_);
    if (progress > rendered_reported_) {
      std::cout << "Rendered " << rendered_ << " pixels: " << progress
          << "%" << std::endl;
      rendered_reported_ = progress + 5.0;
    }
  }
  pixels_[PixelIndex(x, y)] = c;
}
