#include "scene/prepared_computation.h"

#include "primitives/intersection.h"
#include "primitives/math.h"
#include "primitives/ray.h"
#include "shapes/shape.h"

PreparedComputation::PreparedComputation(Intersection i, Ray r) {
  t_ = i.T();
  object_ = (Shape *)i.Object();
  point_ = r.Position(t_);
  eye_vector_ = -r.Direction();
  normal_vector_ = object_->Normal(point_);

  if (normal_vector_.Dot(eye_vector_) < 0) {
    inside_ = true;
    normal_vector_ = -normal_vector_;
  } else {
    inside_ = false;
  }
  over_point_ = point_ + normal_vector_ * EPSILON;
}
