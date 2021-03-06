#include "primitives/color.h"

#include <math.h>
#include <sstream>

Color::Color(float r, float g, float b) : Tuple(r, g, b, 0) {}

const Color Color::Blend(const Color &o) const {
  return Color((this->r() + o.r()) / 2.0,
    (this->g() + o.g()) / 2.0,
    (this->b() + o.b()) / 2.0);
}

Color operator*(const Color c, const Color o) {
  return Color(c.r() * o.r(), c.g() * o.g(), c.b() * o.b());
}

Color operator*(const Color c, float scalar) {
  return Color(c.r() * scalar, c.g() * scalar, c.b() * scalar);
}

Color operator+(const Color c, const Color o) {
  return Color(c.r() + o.r(), c.g() + o.g(), c.b() + o.b());
}

Color operator-(const Color &c, const Color &o) {
  return Color(c.r() - o.r(), c.g() - o.g(), c.b() - o.b());
}

std::string Color::DebugString() const {
  std::stringstream stream;

  stream << "(r: " << this->r() << ", g: " << this->g() << ", b: " << this->b() << ")" << std::endl;
  return stream.str();
}

Color SilverColor() {
  return Color(0.666, 0.6627, 0.6784);
}

Color WhiteColor() {
  return Color(1, 1, 1);
}

Color BlackColor() {
  return Color(0, 0, 0);
}

Color ElectricBlueColor() {
  return Color(0.031, 0.573, 0.816);
}

Color YellowColor() {
  return Color(1, 1, 0);
}

Color PinkColor() {
  return Color(1, 0.753, 0.796);
}

Color OrangeColor() {
  return Color(1, 0.647, 0);
}

Color TealColor() {
   return Color(0, 0.502, 0.502);
}

uint8_t ColorByte(float color_component) {
  if (color_component >= 1.0) {
    return 255;
  } else {
    return color_component * 256.0;
  }
}

float ColorFloat(uint8_t color) {
  return (float)color / 255.0;
}
