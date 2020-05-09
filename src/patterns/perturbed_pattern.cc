#include "patterns/perturbed_pattern.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <math.h>

#include "primitives/tuple.h"

static std::vector<Tuple> corner_positions = std::vector<Tuple> {
  Tuple(Point(0, 0, 0)), // c000
  Tuple(Point(0, 0, 1)), // c001
  Tuple(Point(0, 1, 0)), // c010
  Tuple(Point(0, 1, 1)), // c011

  Tuple(Point(1, 0, 0)), // c100
  Tuple(Point(1, 0, 1)), // c101
  Tuple(Point(1, 1, 0)), // c110
  Tuple(Point(1, 1, 1)), // c111
};

Tuple GradientVector() {
  int tries = 0;
  while (++tries < 100) {
    float x = rand() / (float)RAND_MAX - 0.5;
    float y = rand() / (float)RAND_MAX - 0.5;
    float z = rand() / (float)RAND_MAX - 0.5;
    Tuple vector = Vector(x, y, z);
    if (vector.Magnitude() < 0.5) {
      // It's in the unit sphere.
      return vector.Normalized();
    }
  }
  assert(false);
}

PerturbedPattern::PerturbedPattern(Pattern *pattern) {
  pattern_ = pattern;

  for (std::vector<Tuple>::const_iterator i = corner_positions.begin();
        i != corner_positions.end(); ++i) {
    gradients_.push_back(GradientVector());
  }
}

const Color PerturbedPattern::PatternColorAt(const Tuple &pattern_point) const {
  return pattern_->ColorAt(PerturbedPoint(pattern_point));
}

const Tuple PerturbedPattern::PerturbedPoint(const Tuple &pattern_point) const {
  float x_jitter = PerlinValue(pattern_point);
  float y_jitter = PerlinValue(pattern_point + Point(-0.5, 0.2, 0.1));
  float z_jitter = PerlinValue(pattern_point + Point(0.3, 0.4, -0.4));

  return pattern_point + Point(x_jitter, y_jitter, z_jitter);
}

Tuple UnitPointIfy(const Tuple &point) {
  float x = point.x() - floor(point.x());
  float y = point.y() - floor(point.y());
  float z = point.z() - floor(point.z());
  assert(x >= 0);
  assert(x <= 1);
  assert(y >= 0);
  assert(y <= 1);
  assert(z >= 0);
  assert(z <= 1);
  return Point(x, y, z);
}

float PerturbedPattern::PerlinValue(const Tuple &point) const {
  Tuple unit_point = UnitPointIfy(point);
  // https://en.wikipedia.org/wiki/Trilinear_interpolation
  // [x,y,z]d are all x,y,z since we're operating on the unit point.
  float xd = unit_point.x();
  float yd = unit_point.y();
  float zd = unit_point.z();
  float c00 = DotPattern(0, unit_point) * (1-xd) + DotPattern(4, unit_point) * xd;
  float c01 = DotPattern(1, unit_point) * (1-xd) + DotPattern(5, unit_point) * xd;
  float c10 = DotPattern(2, unit_point) * (1-xd) + DotPattern(6, unit_point) * xd;
  float c11 = DotPattern(3, unit_point) * (1-xd) + DotPattern(7, unit_point) * xd;

  float c0 = c00 * (1 - yd) + c10 * yd;
  float c1 = c01 * (1 - yd) + c11 * yd;

  float c = c0 * (1 - zd) + c1 * zd;

  const float DAMPER = 0.4;
  return DAMPER * c;
}

float PerturbedPattern::DotPattern(const int &corner_index, Tuple &point) const {
  Tuple distance = point - corner_positions[corner_index];
  return gradients_[corner_index].Dot(distance);
}
