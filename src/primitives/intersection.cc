#include "primitives/intersection.h"

Intersection::Intersection(float t, const void *object) {
  t_ = t;
  object_ = object;
}

Intersection::Intersection(float t, const void *object, float u, float v) {
  t_ = t;
  object_ = object;
  u_ = u;
  v_ = v;
}
