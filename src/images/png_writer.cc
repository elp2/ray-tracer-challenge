#include "images/png_writer.h"

#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>

#include "images/crc.h"
#include "primitives/color.h"
#include "zlib.h"

static const uint8_t SIGNATURE[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

PNGWriter::PNGWriter(Canvas *canvas) {
  canvas_ = canvas;
}

void PNGWriter::WriteFile(std::string filename) const {
  std::ofstream out;
  out.open(filename);
  WriteStream(out);
  out.close();
}

void PNGWriter::WriteStream(std::ostream &stream) const {
  WriteSignature(stream);
  WriteHeader(stream);
  WriteImageData(stream);
  WriteFooter(stream);
}

void PNGWriter::WriteSignature(std::ostream &stream) const {
  stream.write((char *)SIGNATURE, 8);
}

void PNGWriter::WriteHeader(std::ostream &stream) const {
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

void PNGWriter::WriteChunk(std::ostream &stream, const int length, const std::string &type, const void *data) const {
  assert(length < pow(2, 31));

  uint32_t network_order_length = htonl((uint32_t)length);
  stream.write((char *)&network_order_length, sizeof(network_order_length));

  stream << type;

  stream.write((char *)data, length);

  uint32_t crc = htonl(CalculateCRC(type, data, length));
  stream.write((char *)&crc, sizeof(crc));
}

void PNGWriter::WriteFooter(std::ostream &stream) const {
  char data[0];
  WriteChunk(stream, 0, "IEND", data);
}

void PNGWriter::WriteImageData(std::ostream &stream) const {
  // Data stored in scanlines left to right, as 3 bytes of R, G, B
  // with a filter byte (0 for none) before each scanline.
  int uncompressed_length = canvas_->width() * canvas_->height() * 3
      + canvas_->height();
  uint8_t *uncompressed_idata = new uint8_t[uncompressed_length];

  int i = 0;
  for (int y = 0; y < canvas_->height(); ++y) {
    // None type filter byte.
    uncompressed_idata[i++] = 0;
    for (int x = 0; x < canvas_->width(); ++x) {
      Color c = canvas_->PixelAt(x, y);
      uncompressed_idata[i++] = ColorByte(c.r());
      uncompressed_idata[i++] = ColorByte(c.g());
      uncompressed_idata[i++] = ColorByte(c.b());
    }
  }

  uLongf compressed_length = uncompressed_length + 100;
  uint8_t *compressed_data = new uint8_t[compressed_length];
  compress(compressed_data, &compressed_length, uncompressed_idata, uncompressed_length);

  WriteChunk(stream, compressed_length, "IDAT", compressed_data);
}

uint32_t PNGWriter::CalculateCRC(const std::string &type, const void *data, const int length) const {
  int combined_length = type.size() + length;
  char *type_data = new char[combined_length];
  strcpy(type_data, type.c_str());
  memcpy(type_data + 4, data, length);

  uint32_t crc = calculate_crc(type_data, combined_length);
  free(type_data);

  return crc;
}
