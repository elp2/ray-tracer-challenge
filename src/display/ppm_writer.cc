#include "display/ppm_writer.h"

#include <math.h>

#include <iostream>
#include <fstream>

const int MAX_COLOR_VALUE = 255;
const int MAX_LINE_LEN = 70;

PPMWriter::PPMWriter(Canvas *canvas) {
  canvas_ = canvas;
}

bool PPMWriter::WriteFile(std::string filename) {
  std::ofstream out;
  out.open(filename);
  WriteStream(out);
  out.close();
}

void PPMWriter::WriteHeader(std::ostream &stream) {
  // Header.
  // P3 format.
  stream << "P3\n";
  // Width, height.
  stream << canvas_->width() << " " << canvas_->height() << "\n";
  // Maximum Color Value of 255.
  stream << MAX_COLOR_VALUE << "\n";
}

int PPMWriter::ColorInt(float color) {
  if (color >= 1.0) {
    return 255;
  } else if (color < 0.0) {
    return 0;
  } else {
    return ceil(color * 255);
  }
}

void PPMWriter::WriteColorFloat(std::ostream &stream, float fcolor, int *line_len, bool row_end) {
  int color_len;
  int color = ColorInt(fcolor);
  if (color >= 100) {
    color_len = 3;
  } else if (color >= 10) {
    color_len = 2;
  } else {
    color_len = 1;
  }
  bool space_before = *line_len != 0;
  if ((*line_len + color_len + (space_before ? 1 : 0)) >= MAX_LINE_LEN) {
    stream << "\n";
    *line_len = 0;
  } else if (space_before) {
    stream << " ";
    *line_len += 1;
  }

  *line_len += color_len;
  stream << color;
}

void PPMWriter::WriteRow(std::ostream &stream, int y) {
  int line_len = 0;
  for (int x = 0; x < canvas_->width(); x++) {
    bool row_end = x == canvas_->width() - 1;
    Color color = canvas_->PixelAt(x, y);
    WriteColorFloat(stream, color.r(), &line_len, false);
    WriteColorFloat(stream, color.g(), &line_len, false);
    WriteColorFloat(stream, color.b(), &line_len, row_end);
    if (row_end) {
      stream << "\n";
    }
  }
}

void PPMWriter::WriteStream(std::ostream &stream) {
  WriteHeader(stream);
  for (int y = 0; y < canvas_->height(); y++ ){
    WriteRow(stream, y);
  }
}
