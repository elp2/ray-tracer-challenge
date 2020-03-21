#ifndef RTC_PRIMITIVES_MATRIX_H_
#define RTC_PRIMITIVES_MATRIX_H_

#include <vector>

class Matrix {
 public:
  Matrix(int w, int h);
  Matrix(int w, int h, std::vector<float> values);
  ~Matrix() = default;

  float operator()(int row, int col);
  void Set(float value, int row, int col);

 private:
  int w_, h_;
  float *matrix_;
  inline int MatrixIndex(int row, int col);
};

#endif    // RTC_PRIMITIVES_MATRIX_H_
