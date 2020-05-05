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
  const void WriteFile(std::string filename) const;
  // Writes into an arbitrary stream. Mostly used for testing.
  const void WriteStream(std::ostream &stream) const;

 private:
  Canvas *canvas_;

  // Writes PNG signature 8 bits.
  const void WriteSignature(std::ostream &stream) const;
  // Writes Header that must follow the signature.
  const void WriteHeader(std::ostream &stream) const;
  // Writes Image Data. May write multiple chunks.
  const void WriteImageData(std::ostream &stream) const;
  // Writes footer that ends the PNG file.
  const void WriteFooter(std::ostream &stream) const;

  // Writes data for a chunk. Compression and must be done by caller. length must be less than 2^31.
  const void WriteChunk(std::ostream &stream, const int length, const std::string &type, const void *data) const;
  // Returns 4 bit CRC for data.
  const uint32_t CalculateCRC(const std::string &type, const void *data, const int length) const;
};

#endif    // RTC_DISPLAY_PNG_WRITER_H
