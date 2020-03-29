#include "primitives/intersection.h"

Intersection::Intersection(float t, const void *object) {
  t_ = t;
  object_ = object;
}
