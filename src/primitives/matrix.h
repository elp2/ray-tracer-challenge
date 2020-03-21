#ifndef RTC_PRIMITIVES_MATRIX_H_
#define RTC_PRIMITIVES_MATRIX_H_

class Matrix {
 public:
  Matrix(int w, int h);
  ~Matrix() = default;

  float operator()(int x, int y);
  void Set(float value, int x, int y);

 private:
  int w_, h_;
  float *matrix_;
  inline int MatrixIndex(int x, int y);
};

#endif    // RTC_PRIMITIVES_MATRIX_H_
