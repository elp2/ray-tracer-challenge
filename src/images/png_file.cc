#include "images/png_file.h"

#include <cassert>
#include "zlib.h"

// This is a guess, assuming that size of the chunk will not go over 16384
const uLongf CHUNK_DATA_SIZE = 16384;

PNGFile::PNGFile() {
  pixels_ = new std::vector<Color>();
}

void PNGFile::HandleIDATData(uint8_t *data, int len) {
  uint8_t *uncompressed = new uint8_t[CHUNK_DATA_SIZE];
  uLongf data_size = CHUNK_DATA_SIZE;
  int success = uncompress(uncompressed, &data_size, data, len);
  assert(Z_OK == success);

  ParsePixels(uncompressed, data_size);
}

void PNGFile::ParsePixels(uint8_t *data, int len) {
  for (int i = 0; i < len; ++i) {
    int row_pos = pixel_step_ % (3 * width() + 1);
    ++pixel_step_;

    row_pos -= 1; // Trim off filter byte.
    if (row_pos == -1) {
      continue;
    }

    float color = ColorFloat(data[i]);
    int color_step = row_pos % 3;
    if (0 == color_step) {
      partial_r_ = color;
    } else if (1 == color_step) {
      partial_g_ = color;
    } else if (2 == color_step) {
      pixels_->push_back(Color(partial_r_, partial_g_, color));
    }
  }
}
