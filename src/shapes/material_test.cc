#include "gtest/gtest.h"

#include "primitives/color.h"

#include "shapes/material.h"

class MaterialTest : public ::testing::Test {
 protected:
  MaterialTest() {};
  ~MaterialTest() {};
};

TEST(MaterialTest, DefaultMaterial) {
  Material m = Material();
  ASSERT_EQ(m.color(), Color(1.0, 1.0, 1.0));
  ASSERT_FLOAT_EQ(m.ambient(), 0.1);
  ASSERT_FLOAT_EQ(m.diffuse(), 0.9);
  ASSERT_FLOAT_EQ(m.specular(), 0.9);
  ASSERT_FLOAT_EQ(m.shininess(), 200.0);
}
