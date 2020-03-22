#include "primitives/matrix.h"
#include "primitives/transformation.h"

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
