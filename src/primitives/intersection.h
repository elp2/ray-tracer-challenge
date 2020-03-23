#ifndef RTC_PRIMITIVES_INTERSECTION_H
#define RTC_PRIMITIVES_INTERSECTION_H

class Intersection {
 public:
  Intersection(float t);
  ~Intersection() = default;

  float T() const { return t_; };

 private:
  float t_;
};

#endif    // RTC_PRIMITIVES_INTERSECTION_H
