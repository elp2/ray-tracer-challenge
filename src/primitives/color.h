#ifndef RTC_PRIMITIVES_COLOR_H_
#define RTC_PRIMITIVES_COLOR_H_

#include "primitives/tuple.h"

class Color : public Tuple {
 public:
  Color(float r, float g, float b);
  ~Color() = default;

  float r() const { return this->x(); }
  float g() const { return this->y(); }
  float b() const { return this->z(); }
};

// Hadmard Product.
Color operator*(const Color c, const Color o);

#endif    // RTC_PRIMITIVES_COLOR_H_
