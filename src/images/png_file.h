#ifndef RTC_DISPLAY_PNG_FILE_H
#define RTC_DISPLAY_PNG_FILE_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "primitives/color.h"

class PNGFile {
 public:
  PNGFile(int width, int height);
  ~PNGFile() = default;
  int width() const { return width_; };
  int height() const { return height_; };

  void HandleIDATData(uint8_t *data, int len);

  // Returns the underlying pixels. Error if not filled in.
  std::vector<Color> *pixels();

  // Exposed for testing.
  void ParsePixels(uint8_t *data, int len);

 private:
  uint8_t Recon(int row_pos, int filter, uint8_t data) const;

  int width_;
  int height_;

  // Stored by row.
  std::vector<Color> *pixels_;
  uint8_t *current_row_;
  uint8_t *previous_row_;
  // Which pixel step is being written.
  // Is either the filter type, or rgb triplets (row = 1 + 3 * w steps).
  int pixel_step_ = 0;
  float partial_r_, partial_g_;

  // We must concatenate all IDAT chunks and compress at end.
  uint8_t *idat_ = nullptr;
  int idat_len_ = 0;
};

uint8_t AverageFilter(uint8_t a, uint8_t b);
uint8_t PaethPredictor(uint8_t a, uint8_t b, uint8_t c);

#endif    // RTC_DISPLAY_PNG_FILE_H
