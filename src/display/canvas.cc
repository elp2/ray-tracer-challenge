#include "display/canvas.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <mutex>

#include "primitives/color.h"

std::mutex mutex_;

const float PROGRESS_STEP = 0.05;

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
    float progress = Progress();
    if (progress > rendered_reported_) {
      std::cout << "Rendered " << rendered_ << " pixels: " << (100.0 *  progress)
          << "%" << std::endl;
      rendered_reported_ = progress + PROGRESS_STEP;
    }
  }
  Color here = PixelAt(x, y);
  int idx = PixelIndex(x, y);
  data_[idx++] = c.r();
  data_[idx++] = c.g();
  data_[idx++] = c.b();
}

void Canvas::Reset() {
  report_render_progress_ = false;
  for (int y = 0; y < h_; ++y) {
    for (int x = 0; x < w_; ++x) {
      WritePixel(Color(0, 0, 0), x, y);
    }
  }
  report_render_progress_ = true;
  rendered_ = 0;
  rendered_reported_ = PROGRESS_STEP;
}

float Canvas::Progress() const {
  return (float)rendered_ / (float)(w_ * h_);
}