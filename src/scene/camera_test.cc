#include "gtest/gtest.h"

#include <math.h>

#include "display/canvas.h"
#include "primitives/ray.h"
#include "primitives/transformation.h"
#include "scene/camera.h"
#include "scene/world.h"
#include "scene/view_transformation.h"

class CameraTest : public ::testing::Test {
 protected:
  CameraTest() {};
  ~CameraTest() {};
};

TEST(CameraTest, Init) {
  Camera c = Camera(160, 120, M_PI / 2.0);

  ASSERT_EQ(c.width(), 160);
  ASSERT_EQ(c.height(), 120);
  ASSERT_FLOAT_EQ(c.field_of_view(), M_PI / 2.0);
  ASSERT_EQ(c.transform(), IdentityMatrix(4));
}

TEST(CameraTest, PixelSizeForHorizontalCanvas) {
  Camera c = Camera(200, 125, M_PI / 2.0);
  ASSERT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(CameraTest, PixelSizeForVerticalCanvas) {
  Camera c = Camera(125, 200, M_PI / 2.0);
  ASSERT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(CameraTest, RayThroughCenter) {
  Camera c = Camera(201, 101, M_PI / 2.0);
  Ray r = c.RayForPixel(100, 50, Point(0, 0, 0));
  ASSERT_EQ(r.Origin(), Point(0.0, 0.0, 0.0));
  ASSERT_EQ(r.Direction(), Vector(0.0, 0.0, -1.0));
}

TEST(CameraTest, RayThroughCorner) {
  Camera c = Camera(201, 101, M_PI / 2.0);
  Ray r = c.RayForPixel(0, 0, Point(0, 0, 0));
  ASSERT_EQ(r.Origin(), Point(0.0, 0.0, 0.0));
  ASSERT_EQ(r.Direction(), Vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayThroughTransformedCamera) {
  Camera c = Camera(201, 101, M_PI / 2.0);
  c.set_transform(RotationY(M_PI / 4.0) * Translation(0.0, -2.0, 5.0));
  Ray r = c.RayForPixel(100, 50, Point(0, 0, 0));
  ASSERT_EQ(r.Origin(), Point(0.0, 2.0, -5.0));
  ASSERT_EQ(r.Direction(), Vector(sqrt(2.0) / 2.0, 0.0, -sqrt(2.0) / 2.0));
}

TEST(CameraTest, RenderWorld) {
  Camera c = Camera(11, 11, M_PI / 2.0);
  Tuple from = Point(0.0, 0.0, -5.0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));

  World w = DefaultWorld();
  Canvas canvas = c.Render(w);
  ASSERT_EQ(canvas.PixelAt(5, 5), Color(0.38066, 0.47583, 0.2855));
}