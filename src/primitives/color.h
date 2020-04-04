#ifndef RTC_PRIMITIVES_COLOR_H_
#define RTC_PRIMITIVES_COLOR_H_

#include "primitives/tuple.h"

class Color : public Tuple {
 public:
  Color() {};
  Color(float r, float g, float b);
  ~Color() = default;

  float r() const { return this->x(); }
  float g() const { return this->y(); }
  float b() const { return this->z(); }

  // Debug Printing for Tests.
  std::string DebugString() const;
  friend void PrintTo(const Color& color, std::ostream* os) { *os << color.DebugString(); };
};

// Hadmard Product.
Color operator*(const Color c, const Color o);
Color operator*(const Color c, const float factor);
Color operator+(const Color c, const Color o);

#endif    // RTC_PRIMITIVES_COLOR_H_
