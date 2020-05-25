#ifndef RTC_DISPLAY_PNG_FILE_H
#define RTC_DISPLAY_PNG_FILE_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "primitives/color.h"

class PNGFile {
 public:
  PNGFile();
  ~PNGFile() = default;
  void set_width(int width) { width_ = width; };
  int width() const { return width_; };
  void set_height(int height) { height_ = height; };
  int height() const { return height_; };

  void HandleIDATData(uint8_t *data, int len);

  // Returns the underlying pixels. Error if not filled in.
  std::vector<Color> *pixels() const { return pixels_; };

  // Exposed for testing.
  void ParsePixels(uint8_t *data, int len);

 private:
  int width_;
  int height_;

  // Stored by row.
  std::vector<Color> *pixels_;
  // Which pixel step is being written.
  // Is either the filter type, or rgb triplets (row = 1 + 3 * w steps).
  int pixel_step_ = 0;
  float partial_r_, partial_g_;
};

#endif    // RTC_DISPLAY_PNG_FILE_H
