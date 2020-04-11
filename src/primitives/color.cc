#include "primitives/color.h"

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
  return Color(c.x() * scalar, c.y() * scalar, c.z() * scalar);
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
