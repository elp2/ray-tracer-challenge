#include "primitives/tuple.h"
#include "primitives/math.h"

#include <cmath>
#include <iostream>

Tuple::Tuple(float x, float y, float z, float w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
};

bool Tuple::IsPoint() const {
  return epsilon_eq(1.0, w_);
}

bool Tuple::IsVector() const {
  return epsilon_eq(0.0, w_);
}

float Tuple::Magnitude() const {
  return std::sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z() + this->w() + this->w());
}

Tuple Tuple::Normalized() const {
  float magnitude = this->Magnitude();
  return Tuple(this->x() / magnitude, this->y() / magnitude, this->z() / magnitude, this->w() / magnitude);
}

float Tuple::Dot(Tuple other) const {
  return this->x() * other.x() + this->y() * other.y() + this->z() * other.z() + this->w() * other.w();
}

Tuple Tuple::Cross(Tuple other) const {
  return Vector(this->y() * other.z() - this->z() * other.y(),
    this->z() * other.x() - this->x() * other.z(),
    this->x() * other.y() - this->y() * other.x());
}

Tuple Tuple::Reflect(Tuple normal) const {
  Tuple reflected = (*this) - normal * this->Dot(normal) * 2;
  return reflected;
}

Tuple Point(float x, float y, float z) {
  return Tuple(x, y, z, 1.0);
}

Tuple Vector(float x, float y, float z) {
  return Tuple(x, y, z, 0.0);
}

void Tuple::Debug() const {
  std::cout << "Tuple: " << this->x() << ", " << this->y() << ", " << this->z() << ", " << this->w() << std::endl;
}

bool operator==(const Tuple lhs, const Tuple rhs) {
  return epsilon_eq(lhs.x(), rhs.x()) &&
    epsilon_eq(lhs.y(), rhs.y()) &&
    epsilon_eq(lhs.z(), rhs.z()) &&
    epsilon_eq(lhs.w(), rhs.w());
}

Tuple operator+(const Tuple lhs, const Tuple rhs) {
  return Tuple(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w());
}

Tuple operator-(const Tuple lhs, const Tuple rhs) {
  return Tuple(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(), lhs.w() - rhs.w());
}

Tuple operator-(const Tuple neg) {
  return Tuple(-neg.x(), -neg.y(), -neg.z(), -neg.w());
}

Tuple operator*(const Tuple t, float scalar) {
  return Tuple(t.x() * scalar, t.y() * scalar, t.z() * scalar, t.w() * scalar);
}

Tuple operator/(const Tuple t, float div) {
  return Tuple(t.x() / div, t.y() / div, t.z() / div, t.w() / div);
}
