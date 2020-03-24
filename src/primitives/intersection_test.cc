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

TEST(IntersectionTest, AllPositiveT) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(1.0, &s);
  Intersection i2 = Intersection(2.0, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
  Intersection i = xs.Hit().value();
  ASSERT_EQ(xs.Hit().value(), i1);
}

TEST(IntersectionTest, MixedPositiveT) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-1.0, &s);
  Intersection i2 = Intersection(1.0, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
  ASSERT_EQ(xs.Hit().value(), i2);
}

TEST(IntersectionTest, AllNegativeT) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(-2.0, &s);
  Intersection i2 = Intersection(-1.0, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
  ASSERT_FALSE(xs.Hit().has_value());
}

TEST(IntersectionTest, UnsortedList) {
  Sphere s = Sphere();
  Intersection i1 = Intersection(5.0, &s);
  Intersection i2 = Intersection(7.0, &s);
  Intersection i3 = Intersection(-3.0, &s);
  Intersection i4 = Intersection(2.0, &s);

  Intersections xs = Intersections(std::vector<Intersection>{i1, i2, i3, i4});
  ASSERT_EQ(xs.Hit().value(), i4);
}
