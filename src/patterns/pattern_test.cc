#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "patterns/striped_pattern.h"

#include "primitives/color.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/sphere.h"

class PatternMock : public Pattern {
 public:
  const Color PatternColorAt(const Tuple &object_point) const {
    return Color(object_point.x(), object_point.y(), object_point.z());
  }
};

class PatternTest : public ::testing::Test {
 protected:
  PatternTest() {};
  ~PatternTest() {};
  Color white_ = Color(1, 1, 1);
  Color black_ = Color(0, 0, 0);
};

TEST_F(PatternTest, DefaultIdentityTransform) {
  auto pattern = PatternMock();
  ASSERT_EQ(IdentityMatrix(4), pattern.transform());
}

TEST_F(PatternTest, SetsTransform) {
  auto pattern = PatternMock();
  Matrix m = Translation(1, 2, 3);
  pattern.set_transform(m);
  ASSERT_EQ(m, pattern.transform());
}

TEST_F(PatternTest, PatternWithObjectTransformation) {
  Sphere s = Sphere();
  s.SetTransform(Scaling(2, 2, 2));

  Material m = Material();
  auto pattern = new PatternMock();
  m.set_pattern(pattern);
  s.set_material(m);

  ASSERT_EQ(Color(1, 1.5, 2), s.PatternAt(Point(2, 3, 4)));
}

TEST_F(PatternTest, PatternWithTransformation) {
  Sphere s = Sphere();

  Material m = Material();
  auto pattern = new PatternMock();
  pattern->set_transform(Scaling(2, 2, 2));
  m.set_pattern(pattern);
  s.set_material(m);

  ASSERT_EQ(Color(1, 1.5, 2), s.PatternAt(Point(2, 3, 4)));
}

TEST_F(PatternTest, PatternAndObjectTransformation) {
  Sphere s = Sphere();
  s.SetTransform(Scaling(2, 2, 2));

  Material m = Material();
  auto pattern = new PatternMock();
  pattern->set_transform(Translation(0.5, 1, 1.5));
  m.set_pattern(pattern);
  s.set_material(m);

  ASSERT_EQ(Color(0.75, 0.5, 0.25), s.PatternAt(Point(2.5, 3, 3.5)));
}
