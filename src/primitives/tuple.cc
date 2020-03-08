#include "primitives/tuple.h"
#include "primitives/math.h"

#include <iostream>

Tuple::Tuple(float x, float y, float z, float w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
};

bool Tuple::IsPoint() {
  return epsilon_eq(1.0, w_);
}

bool Tuple::IsVector() {
  return epsilon_eq(0.0, w_);
}

Tuple TupleFromPoint(float x, float y, float z) {
  return Tuple(x, y, z, 1.0);
}

Tuple TupleFromVector(float x, float y, float z) {
  return Tuple(x, y, z, 0.0);
}

const void Tuple::Debug() {
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
