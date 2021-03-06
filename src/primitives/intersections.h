#ifndef RTC_PRIMITIVES_INTERSECTIONS_H
#define RTC_PRIMITIVES_INTERSECTIONS_H

#include <optional>
#include <vector>

#include "primitives/intersection.h"

class Intersections {
 public:
  Intersections(std::vector<Intersection> intersections);
  ~Intersections() = default;

  std::optional<Intersection> Hit() const;
  std::size_t Size() const { return intersections_.size(); };
  const std::vector<Intersection> &intersections() const { return intersections_; };
  Intersection operator[](int);

  void Merge(Intersections xs);

 protected:
  std::vector<Intersection> intersections_;
};

#endif    // RTC_PRIMITIVES_INTERSECTIONS_H
