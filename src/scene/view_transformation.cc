#include "scene/view_transformation.h"

#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

Matrix ViewTransformation(Tuple from, Tuple to, Tuple up) {
  Tuple forward = (to - from).Normalized();
  Tuple up_normalized = up.Normalized();
  Tuple left = forward.Cross(up_normalized);
  Tuple true_up = left.Cross(forward);

  Matrix orientation = Matrix(4, 4, std::vector<float> {
    left.x(), left.y(), left.z(), 0.0,
    true_up.x(), true_up.y(), true_up.z(), 0.0,
    -forward.x(), -forward.y(), -forward.z(), 0.0,
    0.0, 0.0, 0.0, 1.0
  });

  return orientation * Translation(-from.x(), -from.y(), -from.z());
}
