#include "primitives/perlin_noise.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

const int NUM_GRADIENTS = 101;

Tuple GradientVector() {
  int tries = 0;
  while (++tries < 100) {
    float x = rand() / (float)(RAND_MAX / 2.0) - 1;
    float y = rand() / (float)(RAND_MAX / 2.0) - 1;
    float z = rand() / (float)(RAND_MAX / 2.0) - 1;
    Tuple vector = Vector(x, y, z);
    if (vector.Magnitude() < 1) {
      // It's in the unit sphere.
      return vector.Normalized();
    }
  }
  assert(false);
}

PerlinNoise::PerlinNoise() {
  for (int i =0; i < NUM_GRADIENTS; ++i) {
    gradients_.push_back(GradientVector());
  }
}

float PerlinNoise::PerlinValue(const Tuple &point) const {
  // https://en.wikipedia.org/wiki/Trilinear_interpolation

  float x0 = floor(point.x());
  float x1 = ceil(point.x());
  if (x0 == x1) {
    x1 = x0 + 1;
  }

  float y0 = floor(point.y());
  float y1 = ceil(point.y());
  if (y0 == y1) {
    y1 = y0 + 1;
  }

  float z0 = floor(point.z());
  float z1 = ceil(point.z());
  if (z0 == z1) {
    z1 = z0 + 1;
  }

  float xd = (point.x() - x0) / (x1 - x0);
  float yd = (point.y() - y0) / (y1 - y0);
  float zd = (point.z() - z0) / (z1 - z0);
  float c00 = DotCubeGradient(Point(x0, y0, z0), point) * (1-xd)
      + DotCubeGradient(Point(x1, y0, z0), point) * xd;
  float c01 = DotCubeGradient(Point(x0, y0, z1), point) * (1-xd)
      + DotCubeGradient(Point(x1, y0, z1), point) * xd;
  float c10 = DotCubeGradient(Point(x0, y1, z0), point) * (1-xd)
      + DotCubeGradient(Point(x1, y1, z0), point) * xd;
  float c11 = DotCubeGradient(Point(x0, y1, z1), point) * (1-xd)
      + DotCubeGradient(Point(x1, y1, z1), point) * xd;

  float c0 = c00 * (1 - yd) + c10 * yd;
  float c1 = c01 * (1 - yd) + c11 * yd;

  float c = c0 * (1 - zd) + c1 * zd;
  return c;
}

float PerlinNoise::DotCubeGradient(const Tuple &corner, const Tuple &point) const {
  Tuple distance = point - corner;
  return Gradient(corner.x(), corner.y(), corner.z()).Dot(distance);
}

const Tuple PerlinNoise::Gradient(float x, float y, float z) const {
  // Hacky Hash.
  int gradient_index = round(2 * x + 3 * y + 8 * z + y * z - 0.2 * x * z);
  if (gradient_index < 0) {
    gradient_index = NUM_GRADIENTS - gradient_index;
  }

  return gradients_[gradient_index % NUM_GRADIENTS];
}
