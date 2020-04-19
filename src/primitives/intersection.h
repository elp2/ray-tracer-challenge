#ifndef RTC_PRIMITIVES_INTERSECTION_H
#define RTC_PRIMITIVES_INTERSECTION_H

class Intersection {
 public:
  Intersection(float t, const void *object);
  Intersection(float t, const void *object, float u, float v);
  ~Intersection() = default;

  float T() const { return t_; };
  const void *Object() const { return object_; };
  bool operator==(Intersection other) const { return object_ == other.Object() && t_ == other.T(); };

  const float u() const { return u_; };
  const float v() const { return v_; };

 private:
  float t_;
  const void *object_;
  float u_;
  float v_;
};

#endif    // RTC_PRIMITIVES_INTERSECTION_H
