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

  const Color Blend(const Color &color) const;

  // Debug Printing for Tests.
  std::string DebugString() const;
  friend void PrintTo(const Color& color, std::ostream* os) { *os << color.DebugString(); };
};

// Returns a 0.0-1.0 ranged color as 0-255 byte.
uint8_t ColorByte(float color_component);

// Transforms a 0-255 byte into 0.0-1.0 ranged color.
float ColorFloat(uint8_t color);

// Hadmard Product.
Color operator*(const Color c, const Color o);
Color operator*(const Color c, const float factor);
Color operator+(const Color c, const Color o);
Color operator-(const Color &c, const Color &o);

Color SilverColor();
Color WhiteColor();
Color BlackColor();
Color ElectricBlueColor();
Color YellowColor();
Color PinkColor();
Color OrangeColor();
Color TealColor();

#endif    // RTC_PRIMITIVES_COLOR_H_
