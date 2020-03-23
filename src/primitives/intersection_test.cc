#include "gtest/gtest.h"

#include "primitives/intersection.h"
#include "shapes/sphere.h"

#include <vector>

class IntersectionTest : public ::testing::Test {
 protected:
  IntersectionTest() {};
  ~IntersectionTest() {};
};

TEST(IntersectionTest, Encapsulation) {
  Sphere s = Sphere();
  Intersection i = Intersection(3.5, &s);
  ASSERT_EQ(&s, i.Object());
}
