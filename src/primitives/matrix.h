#ifndef RTC_PRIMITIVES_MATRIX_H_
#define RTC_PRIMITIVES_MATRIX_H_

class Matrix {
 public:
  Matrix(int w, int h);
  ~Matrix() = default;

 private:
  int w_, h_;
};

#endif    // RTC_PRIMITIVES_MATRIX_H_
