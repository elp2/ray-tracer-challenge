#ifndef RTC_PRIMITIVES_TUPLE_H_
#define RTC_PRIMITIVES_TUPLE_H_

class Tuple {
 public:
  Tuple(float x, float y, float z, float w);
  ~Tuple() = default;

  float x() const { return x_; }
  float y() const { return y_; }
  float z() const { return z_; }
  float w() const { return w_; }

  bool IsPoint();
  bool IsVector();

 private:
  float x_, y_, z_, w_;
};

Tuple *point(float x, float y, float z);
Tuple *vector(float x, float y, float z);

#endif    // RTC_PRIMITIVES_TUPLE_H_
