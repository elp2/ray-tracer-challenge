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

  float DotCubeGradient(const Tuple &corner, const Tuple &point) const;
  const Tuple Gradient(float x, float y, float z) const;
};

#endif    // RTC_PRIMITIVES_PERLIN_NOISE_H
