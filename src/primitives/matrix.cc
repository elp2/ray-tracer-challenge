#include "primitives/matrix.h"

#include <cassert>
#include <cstdlib>
#include <vector>

#include "primitives/tuple.h"

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

const Matrix operator*(const Matrix lhs, const Matrix rhs) {
  Matrix ret = Matrix(lhs.h(), rhs.w());
  for (int row = 0; row < lhs.h(); ++row) {
    for (int col = 0; col < rhs.w(); ++col) {
      float element = 0;
      for (int i = 0; i < lhs.w(); ++i) {
        element += lhs(row, i) * rhs(i, col);
      }
      ret.Set(element, row, col);
    }
  }
  return ret;
}

const Tuple operator*(const Matrix m, const Tuple t) {
  return Tuple(
    m(0, 0) * t.x() + m(0, 1) * t.y() + m(0, 2) * t.z() + m(0, 3) * t.w(),
    m(1, 0) * t.x() + m(1, 1) * t.y() + m(1, 2) * t.z() + m(1, 3) * t.w(),
    m(2, 0) * t.x() + m(2, 1) * t.y() + m(2, 2) * t.z() + m(2, 3) * t.w(),
    m(3, 0) * t.x() + m(3, 1) * t.y() + m(3, 2) * t.z() + m(3, 3) * t.w()
  );
}

Matrix IdentityMatrix(int dimension) {
  Matrix identity = Matrix(dimension, dimension);
  for (int i = 0; i < dimension; ++i) {
    identity.Set(1, i, i);
  }
  return identity;
}
