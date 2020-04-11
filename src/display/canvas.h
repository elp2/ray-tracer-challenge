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

  void set_report_render_progress(bool report) { report_render_progress_ = report; };

 private:
  Color *pixels_;
  int w_, h_;
  int PixelIndex(int x, int y);

  bool report_render_progress_ = false;
  int rendered_ = 0;
  float rendered_reported_ = 0;
};

#endif    // RTC_DISPLAY_CANVAS_H
