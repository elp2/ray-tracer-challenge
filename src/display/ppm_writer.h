#ifndef RTC_DISPLAY_PPMWRITER_H
#define RTC_DISPLAY_PPMWRITER_H

#include "display/canvas.h"

#include <ostream>

class PPMWriter {
 public:
  PPMWriter(Canvas *canvas);
  ~PPMWriter() = default;

  bool WriteFile();
  void WriteStream(std::ostream &stream);

 private:
  Canvas *canvas_;

  void WriteHeader(std::ostream &stream);
  void WriteRow(std::ostream &stream, int row);
  int ColorInt(float color);
  bool WriteColorFloat(std::ostream &stream, float fcolor, int *line_len);
};

#endif    // RTC_DISPLAY_PPMWRITER_H
