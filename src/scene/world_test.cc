#include "gtest/gtest.h"

#include <algorithm>
#include <math.h>

#include "primitives/transformation.h"
#include "shapes/sphere.h"
#include "scene/world.h"

class WorldTest : public ::testing::Test {
 protected:
  WorldTest() {};
  ~WorldTest() {};
};

TEST(WorldTest, EmptyWorld) {
  World w = World();
  ASSERT_EQ(w.objects().size(), 0);
  ASSERT_EQ(w.light(), PointLight());
}

TEST(WorldTest, IntersectWithRay) {
  World w = DefaultWorld();
  Ray r = Ray(Point(0.0, 0.0, -5.0), Vector(0.0, 0.0, 1.0));
  Intersections xs = w.Intersect(r);
  ASSERT_EQ(xs.Size(), 4);
  ASSERT_FLOAT_EQ(xs[0].T(), 4.0);
  ASSERT_FLOAT_EQ(xs[1].T(), 4.5);
  ASSERT_FLOAT_EQ(xs[2].T(), 5.5);
  ASSERT_FLOAT_EQ(xs[3].T(), 6);
}
