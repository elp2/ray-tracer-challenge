#include "display/canvas.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <mutex>

#include "primitives/color.h"

std::mutex mutex_;

Canvas::Canvas(int w, int h) {
  w_ = w;
  h_ = h;
  data_ = (float *)calloc(sizeof(float), w_ * h_ * 3);
}

int Canvas::PixelIndex(int x, int y) {
  assert(x >= 0);
  assert(x < w_);
  assert(y >= 0);
  assert(y < h_);

  return 3 * (x + y * w_);
}

Color Canvas::PixelAt(int x, int y) {
  int idx = PixelIndex(x, y);
  float r = data_[idx++];
  float g = data_[idx++];
  float b = data_[idx++];
  return Color(r, g, b);
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
  int idx = PixelIndex(x, y);
  data_[idx++] = c.r();
  data_[idx++] = c.g();
  data_[idx++] = c.b();
}
