#include "primitives/tuple.h"
#include "primitives/math.h"

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

Tuple *point(float x, float y, float z) {
  return new Tuple(x, y, z, 1.0);
}

Tuple *vector(float x, float y, float z) {
  return new Tuple(x, y, z, 0.0);
}
