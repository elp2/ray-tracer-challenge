#ifndef RTC_SCENE_CAMERA_H
#define RTC_SCENE_CAMERA_H

#include "primitives/matrix.h"

class Canvas;
class Ray;
class World;

class Camera {
 public:
  Camera(int width, int height, float field_of_view);
  ~Camera() = default;

  int width() { return width_; };
  int height() { return height_; };
  float field_of_view() { return field_of_view_; };
  float pixel_size() { return pixel_size_; };
  Matrix transform() { return transform_; };

  Ray RayForPixel(int x, int y);
  void set_transform(Matrix transform) { transform_ = transform; };

  Canvas Render(World w);

 private:
  int width_ = 0;
  int height_ = 0;
  float field_of_view_ = 0.0;
  Matrix transform_ = IdentityMatrix(4);
  float pixel_size_ = 0.0;
  float half_width_ = 0.0;
  float half_height_ = 0.0;
};

#endif    // RTC_SCENE_CAMERA_H
