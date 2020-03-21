#include "primitives/matrix.h"

#include <cassert>
#include <cstdlib>
#include <vector>

Matrix::Matrix(int w, int h) {
  w_ = h;
  h_ = h;
  matrix_ = (float *)calloc(w * h, sizeof(float));
}

inline int Matrix::MatrixIndex(int x, int y) {
  assert(x >= 0 && x < w_);
  assert(y >= 0 && y < h_);
  return x + y * h_;
}

float Matrix::operator()(int x, int y) {
  return matrix_[MatrixIndex(x, y)];
}

void Matrix::Set(float value, int x, int y) {
  matrix_[MatrixIndex(x, y)] = value;
}
