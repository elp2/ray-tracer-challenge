#include "primitives/matrix.h"

#include <cassert>
#include <cstdlib>
#include <vector>

Matrix::Matrix(int w, int h) {
  w_ = h;
  h_ = h;
  matrix_ = (float *)calloc(w * h, sizeof(float));
}

Matrix::Matrix(int w, int h, std::vector<float> values) {
  w_ = h;
  h_ = h;
  matrix_ = (float *)calloc(w * h, sizeof(float));
  assert(values.size() == w * h);
  for (int i = 0; i < values.size(); ++i) {
    matrix_[i] = values[i];
  }
}

inline int Matrix::MatrixIndex(const int row, const int col) const {
  assert(col >= 0 && col < w_);
  assert(row >= 0 && row < h_);
  return col + row * h_;
}

const float Matrix::operator()(int row, int col) const {
  return matrix_[MatrixIndex(row, col)];
}

void Matrix::Set(float value, int row, int col) {
  matrix_[MatrixIndex(row, col)] = value;
}

const bool operator==(const Matrix lhs, const Matrix rhs) {
  if (lhs.w() != rhs.w() || lhs.h() != rhs.h()) {
    return false;
  }
  for (int row = 0; row < lhs.h(); ++row) {
    for (int col = 0; col < lhs.w(); ++col) {
      if (lhs(row, col) != rhs(row, col)) {
        return false;
      }
    }
  }
  return true;
}

const bool operator!=(const Matrix lhs, const Matrix rhs) {
  return !(lhs == rhs);
}
