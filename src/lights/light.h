#ifndef RTC_LIGHTS_LIGHT_H
#define RTC_LIGHTS_LIGHT_H

class Lightlet;
class Tuple;

#include <vector>

class Light {
 public:
  ~Light() = default;

  virtual const std::vector<const Lightlet *> *LightletsForPoint(const Tuple &p) = 0;
};

#endif    // RTC_LIGHTS_LIGHT_H
