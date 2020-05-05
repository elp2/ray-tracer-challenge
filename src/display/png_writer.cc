#include "display/png_writer.h"

#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <math.h>

#include "display/crc.h"

static const uint8_t SIGNATURE[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

const uint8_t ColorByte(float color_component) {
  int color_int = ceil(color_component * 255.0);
  if (color_int > 255) {
    return 255;
  } else if (color_int < 0) {
    return 0;
  } else {
    return color_int;
  }
}

PNGWriter::PNGWriter(Canvas *canvas) {
  canvas_ = canvas;
}

const void PNGWriter::WriteFile(std::string filename) const {
  std::ofstream out;
  out.open(filename);
  WriteStream(out);
  out.close();
}

const void PNGWriter::WriteStream(std::ostream &stream) const {
  WriteSignature(stream);
  WriteHeader(stream);
  WriteImageData(stream);
  WriteFooter(stream);
}

const void PNGWriter::WriteSignature(std::ostream &stream) const {
  stream.write((char *)SIGNATURE, 8);
}

const void PNGWriter::WriteHeader(std::ostream &stream) const {
  char data[13];
  uint32_t w = htonl((uint32_t)canvas_->width());
  memcpy(data, &w, sizeof(w));
  uint32_t h = htonl((uint32_t)canvas_->height());
  memcpy(data + 4, &h, sizeof(h));
  data[8] = 8; // 8 Bit Color Depth.
  data[9] = 2; // Colors are RGB Triples (no palette).
  data[10] = 0; // Default compression.
  data[11] = 0; // No filter.
  data[12] = 0; // No interlacing.

  WriteChunk(stream, 13, "IHDR", data);
}

const void PNGWriter::WriteChunk(std::ostream &stream, const int length, const std::string &type, const void *data) const {
  assert(length < pow(2, 31));

  uint32_t network_order_length = htonl((uint32_t)length);
  stream.write((char *)&network_order_length, sizeof(network_order_length));

  stream << type;

  stream.write((char *)data, length);

  uint32_t crc = htonl(CalculateCRC(type, data, length));
  stream.write((char *)&crc, sizeof(crc));
}

const void PNGWriter::WriteFooter(std::ostream &stream) const {
  char data[0];
  WriteChunk(stream, 0, "IEND", data);
}

const void PNGWriter::WriteImageData(std::ostream &stream) const {
  // Data stored row by row, left to right, as 3 bytes of R, G, B.
  char *uncompressed_idata = new char[canvas_->width() * canvas_->height() * 3];

  int i = 0;
  for (int y = 0; y < canvas_->height(); ++y) {
    for (int x = 0; x < canvas_->width(); ++x) {
      Color c = canvas_->PixelAt(x, y);
      uncompressed_idata[i++] = ColorByte(c.r());
      uncompressed_idata[i++] = ColorByte(c.g());
      uncompressed_idata[i++] = ColorByte(c.b());
    }
  }

  // TODO: Compress data.
  char *compressed_data = uncompressed_idata;
  int compressed_length = 9;

  WriteChunk(stream, compressed_length, "IDAT", compressed_data);
}

const uint32_t PNGWriter::CalculateCRC(const std::string &type, const void *data, const int length) const {
  int combined_length = type.size() + length;
  char *type_data = new char[combined_length];
  strcpy(type_data, type.c_str());
  memcpy(type_data + 4, data, length);

  uint32_t crc = calculate_crc(type_data, combined_length);
  free(type_data);

  return crc;
}
