#include "scene/prepared_computation.h"

#include "primitives/intersection.h"
#include "primitives/ray.h"
#include "shapes/sphere.h"

PreparedComputation::PreparedComputation(Intersection i, Ray r) {
  t_ = i.T();
  object_ = i.Object();
  point_ = r.Position(t_);
  eye_vector_ = -r.Direction();
  normal_vector_ = ((Sphere *)object_)->Normal(point_);

  if (normal_vector_.Dot(eye_vector_) < 0) {
    inside_ = true;
    normal_vector_ = -normal_vector_;
  } else {
    inside_ = false;
  }
}
