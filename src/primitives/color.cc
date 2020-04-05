#include "primitives/color.h"

#include <sstream>

Color::Color(float r, float g, float b) : Tuple(r, g, b, 0) {}

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

  stream << "(r: " << this->x() << ", " << this->y() << ", g: " << this->z() << ", b: " << this->w() << ")" << std::endl;
  return stream.str();
}
