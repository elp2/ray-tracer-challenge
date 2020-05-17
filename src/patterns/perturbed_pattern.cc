#include "patterns/perturbed_pattern.h"

#include "primitives/perlin_noise.h"
#include "primitives/tuple.h"

PerturbedPattern::PerturbedPattern(Pattern *pattern) {
  pattern_ = pattern;
  noise_ = new PerlinNoise();
}

const Color PerturbedPattern::PatternColorAt(const Tuple &pattern_point) const {
  return pattern_->ColorAt(PerturbedPoint(pattern_point));
}

const Tuple PerturbedPattern::PerturbedPoint(const Tuple &pattern_point) const {
  float x_jitter = noise_->PerlinValue(pattern_point);
  float y_jitter = noise_->PerlinValue(pattern_point + Point(-0.5, 0.2, 0.1));
  float z_jitter = noise_->PerlinValue(pattern_point + Point(0.3, 0.4, -0.4));

  return pattern_point + Point(x_jitter, y_jitter, z_jitter);
}