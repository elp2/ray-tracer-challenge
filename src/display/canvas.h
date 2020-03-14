#include "primitives/color.h"

class Canvas {
 public:
  Canvas(int w, int h);
  ~Canvas() = default;


  void WritePixel(Color c, int x, int y);
  Color PixelAt(int x, int y);

 private:
  Color *pixels_;
  int w_, h_;
};
