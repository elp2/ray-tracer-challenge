#ifndef RTC_DISPLAY_PPMWRITER_H
#define RTC_DISPLAY_PPMWRITER_H

#include "display/canvas.h"


#include <ostream>
#include <string>

class PPMWriter {
 public:
  PPMWriter(Canvas *canvas);
  ~PPMWriter() = default;

  bool WriteFile(std::string filename);
  void WriteStream(std::ostream &stream);

 private:
  Canvas *canvas_;

  void WriteHeader(std::ostream &stream);
  void WriteRow(std::ostream &stream, int row);
  int ColorInt(float color);
  void WriteColorFloat(std::ostream &stream, float fcolor, int *line_len, bool row_end);
};

#endif    // RTC_DISPLAY_PPMWRITER_H
