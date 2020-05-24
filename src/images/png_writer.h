#ifndef RTC_DISPLAY_PNG_WRITER_H
#define RTC_DISPLAY_PNG_WRITER_H

#include "display/canvas.h"

#include <ostream>
#include <string>

class PNGWriter {
 public:
  PNGWriter(Canvas *canvas);
  ~PNGWriter() = default;

  // Writes contents of canvas into *filename*.
  void WriteFile(std::string filename) const;
  // Writes into an arbitrary stream. Mostly used for testing.
  void WriteStream(std::ostream &stream) const;

 private:
  Canvas *canvas_;

  // Writes PNG signature 8 bits.
  void WriteSignature(std::ostream &stream) const;
  // Writes Header that must follow the signature.
  void WriteHeader(std::ostream &stream) const;
  // Writes Image Data. May write multiple chunks.
  void WriteImageData(std::ostream &stream) const;
  // Writes footer that ends the PNG file.
  void WriteFooter(std::ostream &stream) const;

  // Writes data for a chunk. Compression and must be done by caller. length must be less than 2^31.
  void WriteChunk(std::ostream &stream, const int length, const std::string &type, const void *data) const;
  // Returns 4 bit CRC for data.
  uint32_t CalculateCRC(const std::string &type, const void *data, const int length) const;
};

#endif    // RTC_DISPLAY_PNG_WRITER_H
