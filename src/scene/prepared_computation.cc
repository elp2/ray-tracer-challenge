#include "scene/prepared_computation.h"

#include <algorithm>
#include <cassert>

#include "primitives/intersection.h"
#include "primitives/math.h"
#include "primitives/ray.h"
#include "shapes/shape.h"

PreparedComputation::PreparedComputation(Intersection hit, Ray &r, Intersections &xs) {
  t_ = hit.T();
  object_ = (Shape *)hit.Object();
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
  under_point_ = point_ - normal_vector_ * EPSILON;

  reflect_vector_ = r.Direction().Reflect(normal_vector_);
  CalculateN1N2(xs, hit);
}

void PreparedComputation::CalculateN1N2(Intersections &xs, Intersection &hit) {
  std::vector<const void *> intersected_objects;
  // Possible optimization: Capture exited material in merge step of intersections.
  for (int i = 0; i < xs.Size(); ++i) {
    Intersection x = xs[i];
    if (hit == x) {
      if (intersected_objects.empty()) {
        n1_ = REFRACTIVE_INDEX_VACUUM;
      } else {
        Shape *s = (Shape *)intersected_objects[intersected_objects.size() - 1];
        n1_ = s->material().refractive_index();
      }
    }

    std::vector<const void *>::iterator it
      = std::find(intersected_objects.begin(), intersected_objects.end(), x.Object());
    if (it != intersected_objects.end()) {
      intersected_objects.erase(it);
    } else {
      intersected_objects.push_back(x.Object());
    }

    if (hit == x) {
      if (intersected_objects.empty()) {
        n2_ = REFRACTIVE_INDEX_VACUUM;
      } else {
        Shape *s = (Shape *)intersected_objects[intersected_objects.size() - 1];
        n2_ = s->material().refractive_index();
      }
      return;
    }
  }
  assert(false); // Shouldn't happen.
}
