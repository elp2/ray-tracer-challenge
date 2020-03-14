#ifndef RTC_DISPLAY_CANVAS_H
#define RTC_DISPLAY_CANVAS_H

#include "primitives/color.h"

class Canvas {
 public:
  Canvas(int w, int h);
  ~Canvas() = default;

  void WritePixel(Color c, int x, int y);
  Color PixelAt(int x, int y);

  int width() { return w_; };
  int height() { return h_; };

 private:
  Color *pixels_;
  int w_, h_;
};

#endif    // RTC_DISPLAY_CANVAS_H
