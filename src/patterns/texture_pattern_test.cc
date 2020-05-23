#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "patterns/texture_pattern.h"

#include "primitives/color.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"

#include <vector>

class TexturePatternTest : public ::testing::Test {
 protected:
  TexturePatternTest() {
    Color white = Color(1, 1, 1);
    Color black = Color(0, 0, 0);

    texture_ = new std::vector<Color>();
    texture_->push_back(white);
    texture_->push_back(black);
    texture_->push_back(white);

    texture_->push_back(black);
    texture_->push_back(white);
    texture_->push_back(black);

    texture_->push_back(white);
    texture_->push_back(black);
    texture_->push_back(white);
  };
  ~TexturePatternTest() {};

  std::vector<Color> *texture_;
};

TEST_F(TexturePatternTest, CenterIsWhite) {
  auto tp = TexturePattern(3, 3, texture_);

  ASSERT_EQ(tp.ColorAt(Point(0.5, 0, 0.5)), Color(1, 1, 1));
}

TEST_F(TexturePatternTest, YAxisIgnored) {
  auto tp = TexturePattern(3, 3, texture_);

  for (float x = 0; x <= 1.0; x += 0.1) {
    for (float y = 0; y <= 1.0; y += 0.1) {
      for (float z = 0; z <= 1.0; z += 0.1) {
        ASSERT_EQ(tp.ColorAt(Point(x, y, z)), tp.ColorAt(Point(x, 0, z)));
      }
    }
  }
}

TEST_F(TexturePatternTest, ExtendsBeyond01) {
  auto tp = TexturePattern(3, 3, texture_);

  ASSERT_EQ(tp.ColorAt(Point(1.5, 0, 1.5)), Color(1, 1, 1));
}

TEST_F(TexturePatternTest, InterpolationAcrossEdge) {
  auto tp = TexturePattern(3, 3, texture_);

  ASSERT_EQ(tp.ColorAt(Point(0, 0, 0)), Color(0.5, 0.5, 0.5));
}

TEST_F(TexturePatternTest, Interpolation) {
  auto tp = TexturePattern(3, 3, texture_);

  ASSERT_EQ(tp.ColorAt(Point(1.0/3.0, 0, 1.0/3.0)), Color(0.5, 0.5, 0.5));
}
