#include "primitives/matrix.h"
#include "primitives/transformation.h"

#include <math.h>

Matrix Translation(float x, float y, float z) {
  Matrix translation = IdentityMatrix(4);
  translation.Set(x, 0, 3);
  translation.Set(y, 1, 3);
  translation.Set(z, 2, 3);

  return translation;
}

Matrix Scaling(float x, float y, float z) {
  Matrix scaling = Matrix(4, 4);
  scaling.Set(x, 0, 0);
  scaling.Set(y, 1, 1);
  scaling.Set(z, 2, 2);
  scaling.Set(1, 3, 3);

  return scaling;
}

Matrix RotationX(float radians) {
  Matrix rotation = Matrix(4, 4);
  float cos_r = cos(radians);
  float sin_r = sin(radians);

  rotation.Set(1, 0, 0);
  rotation.Set(cos_r, 1, 1);
  rotation.Set(-sin_r, 1, 2);
  rotation.Set(sin_r, 2, 1);
  rotation.Set(cos_r, 2, 2);
  rotation.Set(1, 3, 3);

  return rotation;
}

Matrix RotationY(float radians) {
  Matrix rotation = Matrix(4, 4);
  float cos_r = cos(radians);
  float sin_r = sin(radians);

  rotation.Set(cos_r, 0, 0);
  rotation.Set(sin_r, 0, 2);
  rotation.Set(1, 1, 1);
  rotation.Set(-sin_r, 2, 0);
  rotation.Set(cos_r, 2, 2);
  rotation.Set(1, 3, 3);

  return rotation;
}

Matrix RotationZ(float radians) {
  Matrix rotation = Matrix(4, 4);
  float cos_r = cos(radians);
  float sin_r = sin(radians);

  rotation.Set(cos_r, 0, 0);
  rotation.Set(-sin_r, 0, 1);
  rotation.Set(sin_r, 1, 0);
  rotation.Set(cos_r, 1, 1);
  rotation.Set(1, 2, 2);
  rotation.Set(1, 3, 3);

  return rotation;
}