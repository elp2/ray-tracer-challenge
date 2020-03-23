#ifndef RTC_PRIMITIVES_INTERSECTION_H
#define RTC_PRIMITIVES_INTERSECTION_H

class Intersection {
 public:
  Intersection(float t, void *object);
  ~Intersection() = default;

  float T() const { return t_; };
  void *Object() const { return object_; };

 private:
  float t_;
  void *object_;
};

#endif    // RTC_PRIMITIVES_INTERSECTION_H
