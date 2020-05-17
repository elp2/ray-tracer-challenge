#ifndef RTC_PRIMITIVES_PERLIN_NOISE_H
#define RTC_PRIMITIVES_PERLIN_NOISE_H

#include "primitives/tuple.h"

#include <math.h>
#include <vector>

class PerlinNoise {
 public:
  PerlinNoise();
  ~PerlinNoise() = default;

  float PerlinValue(const Tuple &point) const;

 private:
  std::vector<Tuple> gradients_;

  float DotPattern(const int &corner_index, Tuple &point) const;
};

#endif    // RTC_PRIMITIVES_PERLIN_NOISE_H
