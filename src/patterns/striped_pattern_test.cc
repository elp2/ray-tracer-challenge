#include "gtest/gtest.h"

#include "patterns/striped_pattern.h"

#include "primitives/color.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/sphere.h"

class StripedPatternTest : public ::testing::Test {
 protected:
  StripedPatternTest() {};
  ~StripedPatternTest() {};
  Color white_ = Color(1, 1, 1);
  Color black_ = Color(0, 0, 0);
};

TEST_F(StripedPatternTest, ColorsAreSaved) {
  StripedPattern sp = StripedPattern(white_, black_);
  ASSERT_EQ(sp.color_a(), white_);
  ASSERT_EQ(sp.color_b(), black_);
}

TEST_F(StripedPatternTest, ConstantInY) {
  StripedPattern sp = StripedPattern(white_, black_);
  Color origin_color = sp.ColorAt(Point(0, 0, 0));
  for (int y = 0; y < 10; ++y) {
    ASSERT_EQ(origin_color, sp.ColorAt(Point(0, y, 0)));
  }
}

TEST_F(StripedPatternTest, ConstantInZ) {
  StripedPattern sp = StripedPattern(white_, black_);
  Color origin_color = sp.ColorAt(Point(0, 0, 0));
  for (int z = 0; z < 10; ++z) {
    ASSERT_EQ(origin_color, sp.ColorAt(Point(0, 0, z)));
  }
}

TEST_F(StripedPatternTest, AlternatesOnX) {
  StripedPattern sp = StripedPattern(white_, black_);
  ASSERT_EQ(sp.ColorAt(Point(0, 0, 0)), white_);
  ASSERT_EQ(sp.ColorAt(Point(0.5, 0, 0)), white_);

  ASSERT_EQ(sp.ColorAt(Point(1.0, 0, 0)), black_);
  ASSERT_EQ(sp.ColorAt(Point(1.5, 0, 0)), black_);

  ASSERT_EQ(sp.ColorAt(Point(2.0, 0, 0)), white_);
  ASSERT_EQ(sp.ColorAt(Point(2.5, 0, 0)), white_);
}

TEST_F(StripedPatternTest, StripesOnTransformedObject) {
  Sphere object = Sphere();
  object.SetTransform(Scaling(2, 2, 2));
  StripedPattern *sp = new StripedPattern(white_, black_);
  Material m = Material();
  m.set_pattern(sp);
  object.set_material(m);

  ASSERT_EQ(object.PatternAt(Point(1.5, 0, 0)), white_);
}

TEST_F(StripedPatternTest, StripesOnPatternTransform) {
  Sphere object = Sphere();
  object.SetTransform(Scaling(2, 2, 2));
  StripedPattern *sp = new StripedPattern(white_, black_);
  sp->set_transform(Scaling(2, 2, 2));
  Material m = Material();
  m.set_pattern(sp);
  object.set_material(m);

  ASSERT_EQ(object.PatternAt(Point(1.5, 0, 0)), white_);
}

TEST_F(StripedPatternTest, StripesOnTransformedObjectAndPattern) {
  Sphere object = Sphere();
  object.SetTransform(Scaling(2, 2, 2));
  StripedPattern *sp = new StripedPattern(white_, black_);
  sp->set_transform(Translation(0.5, 0, 0));
  Material m = Material();
  m.set_pattern(sp);
  object.set_material(m);

  ASSERT_EQ(object.PatternAt(Point(2.5, 0, 0)), white_);
}
