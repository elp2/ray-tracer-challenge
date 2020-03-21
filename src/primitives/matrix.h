#ifndef RTC_PRIMITIVES_MATRIX_H_
#define RTC_PRIMITIVES_MATRIX_H_

#include <vector>

class Tuple;

class Matrix {
 public:
  Matrix(int w, int h);
  Matrix(int w, int h, std::vector<float> values);
  ~Matrix() = default;

  const float operator()(int row, int col) const;
  void Set(float value, int row, int col);

  int w() const { return w_; };
  int h() const { return h_; };

  Matrix Transpose();

 private:
  int w_, h_;
  float *matrix_;
  inline int MatrixIndex(const int row, const int col) const;
};

const bool operator==(const Matrix lhs, const Matrix rhs);
const bool operator!=(const Matrix lhs, const Matrix rhs);
const Matrix operator*(const Matrix lhs, const Matrix rhs);
const Tuple operator*(const Matrix lhs, const Tuple rhs);

// TODO static method.
Matrix IdentityMatrix(int dimension);

#endif    // RTC_PRIMITIVES_MATRIX_H_
