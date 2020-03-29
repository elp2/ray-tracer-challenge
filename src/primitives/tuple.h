#ifndef RTC_PRIMITIVES_TUPLE_H_
#define RTC_PRIMITIVES_TUPLE_H_

#include <string>

class Tuple {
 public:
  Tuple() {};
  Tuple(float x, float y, float z, float w);
  ~Tuple() = default;

  float x() const { return x_; }
  float y() const { return y_; }
  float z() const { return z_; }
  float w() const { return w_; }
  void SetW(float w) { w_ = w; };

  bool IsPoint() const;
  bool IsVector() const;

  float Magnitude() const;
  Tuple Normalized() const;

  float Dot(Tuple other) const;
  Tuple Cross(Tuple other) const;
  Tuple Reflect(Tuple normal) const;

  // Debug Printing for Tests.
  void Debug() const;
  std::string DebugString() const;
  friend void PrintTo(const Tuple& tuple, std::ostream* os) { *os << tuple.DebugString(); };

 private:
  float x_, y_, z_, w_;
};

bool operator==(const Tuple lhs, const Tuple rhs);
Tuple operator+(const Tuple lhs, const Tuple rhs);
Tuple operator-(const Tuple lhs, const Tuple rhs);
Tuple operator-(const Tuple neg);
Tuple operator*(const Tuple t, float scalar);
Tuple operator/(const Tuple t, float div);

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);

#endif    // RTC_PRIMITIVES_TUPLE_H_
