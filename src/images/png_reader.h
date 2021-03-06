#ifndef RTC_DISPLAY_PNG_READER_H
#define RTC_DISPLAY_PNG_READER_H

#include <cstdint>
#include <fstream>
#include <string>

class PNGFile;

struct PNGChunk {
  int length;
  std::string chunk_type;
  uint8_t *data;
};


class PNGReader {
 public:
  PNGReader();
  ~PNGReader() = default;

  // Reads contents of *filename*.
  PNGFile *ReadFile(std::string filename) const;
  // Reads into an arbitrary stream. Mostly used for testing.
  PNGFile *ReadStream(std::istream &stream) const;

 private:
  void ReadSignature(std::istream &stream) const;
  const PNGChunk GetChunk(std::istream &stream) const;
  PNGFile *HandleIHDR(PNGChunk &chunk) const;
  void HandleIDAT(PNGChunk &chunk, PNGFile *png) const;
};

#endif    // RTC_DISPLAY_PNG_READER_H
