#include "images/png_file.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include "math.h"
#include "zlib.h"

// This is a guess, since I'm too lazy to handle Z_BUF_ERROR for now.
const uLongf CHUNK_DATA_SIZE = 1024 * 1024;

PNGFile::PNGFile(int width, int height) {
  width_ = width;
  height_ = height;

  pixels_ = new std::vector<Color>();

  // Keep track of this row and the one above for filtering.
  previous_row_ = new uint8_t[3 * width];
  current_row_ = new uint8_t[3 * width];

  idat_ = new uint8_t[CHUNK_DATA_SIZE];
}

void PNGFile::HandleIDATData(uint8_t *data, int len) {
  memcpy(idat_ + idat_len_, data, len);
  idat_len_ += len;
}

void PNGFile::ParsePixels(uint8_t *data, int len) {
  int row_length = (width() * 3 + 1);
  assert(len == row_length * height());

  uint8_t filter = 0;
  int i = 0;
  for (int y = 0; y < height(); ++y) {
    for (int row_pos = 0; row_pos < width() * 3 + 1; ++row_pos) {
      if (row_pos == 0) {
        filter = data[i];
      } else {
        current_row_[row_pos - 1] = Recon(row_pos - 1, filter, data[i]);
      }
      ++i;
    }
    for (int pi = 0; pi < width() * 3; pi += 3) {
      float r = ColorFloat(current_row_[pi]);
      float g = ColorFloat(current_row_[pi + 1]);
      float b = ColorFloat(current_row_[pi + 2]);
      pixels_->push_back(Color(r, g, b));
    }

    std::swap(previous_row_, current_row_);
  }
}

uint8_t PaethPredictor(uint8_t a, uint8_t b, uint8_t c) {
  int p = a + b - c;
  int pa = abs(p - int(a));
  int pb = abs(p - int(b));
  int pc = abs(p - int(c));

  if (pa <= pb && pa <= pc) {
    return a;
  } else if (pb <= pc) {
    return b;
  } else {
    return c;
  }
}

uint8_t AverageFilter(uint8_t a, uint8_t b) {
  int sum = a + b;
  return sum / 2;
}

uint8_t PNGFile::Recon(int row_pos, int filter, uint8_t x) const {
  if (filter == 0) {
    return x;
  }
  uint8_t a = row_pos >= 3 ? current_row_[row_pos - 3] : 0;
  uint8_t b = previous_row_[row_pos];

  if (filter == 1) {
    return x + a;
  } else if (filter == 2) {
    return x + b;
  } else if (filter == 3) {
    return x + AverageFilter(a, b);
  } else if (filter == 4) {
    uint8_t c = row_pos >= 3 ? previous_row_[row_pos - 3] : 0;
    uint8_t ret = x + PaethPredictor(a, b, c);
    return ret;
  } else {
    std::cout << "Unknown filter type: " << filter << std::endl;
    assert(false);
  }
}

std::vector<Color> *PNGFile::pixels() {
  if (pixels_->size()) {
    return pixels_;
  }

  uint8_t *uncompressed = new uint8_t[CHUNK_DATA_SIZE];
  uLongf data_size = CHUNK_DATA_SIZE;
  int success = uncompress(uncompressed, &data_size, idat_, idat_len_);
  if (success != Z_OK) {
    std::cout << "uncompress error " << success << std::endl;
    assert(Z_OK == success);
  }

  ParsePixels(uncompressed, data_size);

  delete(idat_);

  return pixels_;
}