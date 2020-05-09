#ifndef RTC_PRIMITIVES_MATRIX_H_
#define RTC_PRIMITIVES_MATRIX_H_

#include <ostream>
#include <string>
#include <vector>

class Tuple;

class Matrix {
 public:
  Matrix(int w, int h);
  Matrix(int w, int h, std::vector<float> values);
  ~Matrix();

  Matrix(const Matrix &matrix);
  Matrix &operator=(const Matrix &matrix);

  float operator()(const int &row, const int &col) const;
  void Set(float value, const int &row, const int &col);

  inline int w() const { return w_; };
  inline int h() const { return h_; };

  Matrix Transpose();
  float Determinant() const;
  // Returns a submatrix by removing row and col.
  Matrix SubMatrix(int row, int col) const;
  float Minor(int row, int col) const;
  float Cofactor(int row, int col) const;

  bool Invertible() const;
  Matrix Inverse() const;

  // Debug Printing for Tests.
  void Debug();
  std::string DebugString() const;
  friend void PrintTo(const Matrix& matrix, std::ostream* os) { *os << matrix.DebugString(); };

 private:
  int w_, h_;
  float *matrix_;
  inline int MatrixIndex(const int &row, const int &col) const;
};

bool operator==(const Matrix lhs, const Matrix rhs);
bool operator!=(const Matrix lhs, const Matrix rhs);
const Matrix operator*(const Matrix lhs, const Matrix rhs);
const Tuple operator*(const Matrix lhs, const Tuple rhs);

// TODO static method.
Matrix IdentityMatrix(int dimension);

#endif    // RTC_PRIMITIVES_MATRIX_H_
