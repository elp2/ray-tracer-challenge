#include "primitives/matrix.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "primitives/math.h"
#include "primitives/tuple.h"

Matrix::Matrix(int w, int h) {
  w_ = h;
  h_ = h;
  matrix_ = (float *)calloc(w * h, sizeof(float));
}

Matrix::~Matrix() {
  free(matrix_);
}

Matrix::Matrix(const int w, const int h, std::vector<float> values) {
  w_ = h;
  h_ = h;
  matrix_ = (float *)calloc(w * h, sizeof(float));
  std::vector<float>::size_type matrix_size = w * h;
  assert(values.size() == matrix_size);
  for (std::vector<float>::size_type i = 0; i < values.size(); ++i) {
    matrix_[i] = values[i];
  }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
  if (this != &matrix) {
    if (w_ == matrix.w_ && h_ == matrix.h_) {
      memcpy(matrix_, matrix.matrix_, w_ * h_ * sizeof(float));
    } else {
      w_ = matrix.w_;
      h_ = matrix.h_;
      free(matrix_);
      matrix_ = (float *)malloc(w_ * h_ * sizeof(float));
      memcpy(matrix_, matrix.matrix_, w_ * h_ * sizeof(float));
    }
  }
  return *this;
}

Matrix::Matrix(const Matrix &matrix) {
  w_ = matrix.w();
  h_ = matrix.h();
  matrix_ = (float *)malloc(w_ * h_ * sizeof(float));
  memcpy(matrix_, matrix.matrix_, w_ * h_ * sizeof(float));
}

inline int Matrix::MatrixIndex(const int &row, const int &col) const {
  // assert(col >= 0 && col < w_);
  // assert(row >= 0 && row < h_);
  return col + row * h_;
}

float Matrix::operator()(const int &row, const int &col) const {
  return matrix_[MatrixIndex(row, col)];
}

void Matrix::Set(float value, const int &row, const int &col) {
  matrix_[MatrixIndex(row, col)] = value;
}

bool operator==(const Matrix lhs, const Matrix rhs) {
  if (lhs.w() != rhs.w() || lhs.h() != rhs.h()) {
    return false;
  }
  for (int row = 0; row < lhs.h(); ++row) {
    for (int col = 0; col < lhs.w(); ++col) {
      float l = lhs(row, col);
      float r = rhs(row, col);
      if (!epsilon_eq(r, l)) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const Matrix lhs, const Matrix rhs) {
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

Matrix Matrix::Transpose() {
  Matrix transposed = Matrix(this->w(), this->h());
  for (int row = 0; row < this->h(); ++row) {
    for (int col = 0; col < this->w(); ++col) {
      transposed.Set(this->operator()(row, col), col, row);
    }
  }
  return transposed;
}

float Matrix::Determinant() const {
  if (this->w() == 2) {
    return this->operator()(0, 0) * this->operator()(1, 1) -
      this->operator()(1, 0) * this->operator()(0, 1);
  } else {
    float determinant = 0;
    for (int col = 0; col < this->w(); ++col) {
      determinant += this->operator()(0, col) * this->Cofactor(0, col);
    }
    return determinant;
  }
}

Matrix Matrix::SubMatrix(int rrow, int rcol) const {
  int y = 0;
  Matrix sub = Matrix(this->h() - 1, this->w() - 1);
  for (int r = 0; r < this->h(); ++r) {
    if (r == rrow) {
      continue;
    }
    int x = 0;
    for (int c = 0; c < this->w(); ++c) {
      if (c != rcol) {
        sub.Set(this->operator()(r, c), y, x);
        ++x;
      }
    }
    ++y;
  }
  return sub;
}

float Matrix::Minor(int row, int col) const {
  return this->SubMatrix(row, col).Determinant();
}

float Matrix::Cofactor(int row, int col) const {
  float minor = this->Minor(row, col);
  if ((row + col) % 2 == 1) {
    return -1 * minor;
  } else {
    return minor;
  }
}

bool Matrix::Invertible() const {
  return this->Determinant() != 0;
}

Matrix Matrix::Inverse() const {
  float determinent = this->Determinant();
  Matrix inverse = Matrix(this->h(), this->w());
  for (int row = 0; row < this->h(); ++row) {
    for (int col = 0; col < this->w(); ++col) {
      float cofactor = this->Cofactor(row, col);
      inverse.Set(cofactor / determinent, col, row);
    }
  }
  return inverse;
}

void Matrix::Debug() {
  std::cout << DebugString() << std::endl;
}

std::string Matrix::DebugString() const {
  std::stringstream stream;
  for (int y = 0; y < h_; ++y) {
    for (int x = 0; x < w_; ++x) {
      stream << operator()(y, x);
      if (x == w_ - 1) {
        stream << "\n";
      } else {
        stream << " ";
      }
    }
  }

  return stream.str();
}
