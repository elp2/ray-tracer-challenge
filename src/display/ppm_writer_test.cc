#include "gtest/gtest.h"

#include "display/canvas.h"
#include "display/ppm_writer.h"

#include <ostream>
#include <string>
#include <sstream>

class PPMWriterTest : public ::testing::Test {
 protected:
  PPMWriterTest() {};
  ~PPMWriterTest() {};
};

TEST(PPMWriterTest, HeaderReflectsDimensions) {
  Canvas *canvas = new Canvas(5, 3);
  PPMWriter writer = PPMWriter(canvas);

  std::ostringstream stream;
  writer.WriteStream(stream);

  ASSERT_EQ(std::string("P3\n5 3\n255\n"), stream.str());
}

TEST(PPMWriterTest, PixelContent) {
  Canvas *canvas = new Canvas(5, 3);
  canvas->WritePixel(Color(1.5, 0, 0), 0, 0);
  canvas->WritePixel(Color(0, 0.5,  0), 2, 1);
  canvas->WritePixel(Color(-0.5, 0, 1), 4, 2);
  PPMWriter writer = PPMWriter(canvas);

  std::ostringstream stream;
  writer.WriteStream(stream);

  std::string output = stream.str();
  ASSERT_EQ(std::string("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"), stream.str());
}

TEST(PPMWriterTest, SplitsLongLines) {
  int w = 10;
  int h = 2;
  Canvas *canvas = new Canvas(w, h);
  Color c = Color(1, 0.8, 0.6);
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      canvas->WritePixel(c, x, y);
    }
  }
  PPMWriter writer = PPMWriter(canvas);

  std::ostringstream stream;
  writer.WriteStream(stream);

  std::string output = stream.str();  
  ASSERT_EQ(std::string("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n"), output);
}

TEST(PPMWriterTest, EndsInNewLine) {
  Canvas *canvas = new Canvas(5, 3);
  PPMWriter writer = PPMWriter(canvas);  

  std::ostringstream stream;
  writer.WriteStream(stream);

  std::string output = stream.str();
  ASSERT_EQ(output.at(output.length() - 1), '\n'); 
}
