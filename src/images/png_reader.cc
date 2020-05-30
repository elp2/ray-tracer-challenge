#include "images/png_reader.h"

#include "images/crc.h"
#include "images/png.h"
#include "images/png_file.h"

#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>

PNGReader::PNGReader() {

}

PNGFile *PNGReader::ReadFile(std::string filename) const {
  std::ifstream instream(filename, std::ios::in | std::ios::binary);
  PNGFile *png = ReadStream(instream);
  instream.close();
  return png;
}

PNGFile *PNGReader::ReadStream(std::istream &stream) const {
  PNGFile *png = nullptr;
  ReadSignature(stream);
  while (stream) {
    PNGChunk chunk = GetChunk(stream);
    if (chunk.chunk_type == "IHDR") {
      png = HandleIHDR(chunk);
    } else if (chunk.chunk_type == "IDAT") {
      HandleIDAT(chunk, png);
    } else if (chunk.chunk_type == "pHYs") {
      // Ignore - Phyiscal Pixel dimensions.
    } else if (chunk.chunk_type == "tIME") {
      // Ignore - Image last-modification time.
    } else if (chunk.chunk_type == "IEND") {
      break;
    } else {
      std::cout << "Unknown chunk type: " << chunk.chunk_type << std::endl;
      assert(false);
    }
  }

  return png;
}

void PNGReader::ReadSignature(std::istream &stream) const {
  uint8_t *first_eight = (uint8_t *)calloc(8, sizeof(uint8_t));
  stream.read((char *)first_eight, 8);
  for (int i = 0; i < 8; ++i) {
    assert(PNG_SIGNATURE[i] == first_eight[i]);
  }
}

const PNGChunk PNGReader::GetChunk(std::istream &stream) const {
  PNGChunk chunk;
  uint32_t len;
  stream.read((char *)&len, 4);
  len = htonl(len);
  chunk.length = len;


  char chunk_type[5] = {0, 0, 0, 0, 0};
  stream.read(chunk_type, 4);
  chunk.chunk_type = std::string(chunk_type);

  uint8_t *data = (uint8_t *)calloc(len, sizeof(uint8_t));
  stream.read((char *)data, len);
  chunk.data = data;

  uint32_t crc;
  stream.read((char *)&crc, 4);
  crc = htonl(crc);

  uint32_t calculated_crc = calculate_png_crc(chunk.chunk_type, chunk.data, chunk.length);
  assert(crc == calculated_crc);
  return chunk;
}

PNGFile *PNGReader::HandleIHDR(PNGChunk &chunk) const {
  assert(chunk.length == 13);
  uint32_t w;
  memcpy(&w, chunk.data, sizeof(w));
  w = htonl(w);
  uint32_t h;
  memcpy(&h, chunk.data + 4, sizeof(h));
  h = htonl(h);
  // Confirm it doesn't have any unsupported features.
  assert(chunk.data[8] == 8); // 8 Bit Color Depth.
  assert(chunk.data[9] == 2); // Colors are RGB Triples (no palette).
  assert(chunk.data[10] == 0); // Default compression.
  assert(chunk.data[10] == 0); // No filter.
  assert(chunk.data[10] == 0); // No interlacing.
  PNGFile *png = new PNGFile(w, h);
  return png;
}

void PNGReader::HandleIDAT(PNGChunk &chunk, PNGFile *png) const {
  assert(png != nullptr);
  png->HandleIDATData(chunk.data, chunk.length);
}
