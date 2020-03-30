#include "scene/camera.h"

#include <cassert>
#include <math.h>

#include "display/canvas.h"
#include "primitives/ray.h"
#include "scene/world.h"

Camera::Camera(int width, int height, float field_of_view) {
  assert(width > 0);
  assert(height > 0);
  assert(field_of_view < M_PI);
  assert(field_of_view > 0);

  width_ = width;
  assert(width_);
  height_ = height;
  field_of_view_ = field_of_view;

  float half_view = tan(field_of_view_ / 2);
  float aspect_ratio = (float)width_ / (float)height_;
  if (aspect_ratio >= 1.0) {
    half_width_ = half_view;
    half_height_ = half_view / aspect_ratio;
  } else {
    half_width_ = half_view * aspect_ratio;
    half_height_ = half_view;
  }
  pixel_size_ = (half_width_ * 2.0) / (float)width_;
}

Ray Camera::RayForPixel(int x, int y) {
  float x_offset = (x + 0.5) * pixel_size_;
  float y_offset = (y + 0.5) * pixel_size_;

  float world_x = half_width_ - x_offset;
  float world_y = half_height_ - y_offset;

  Tuple pixel = transform_.Inverse() * Point(world_x, world_y, -1.0);
  Tuple origin = transform_.Inverse() * Point(0.0, 0.0, 0.0);
  Tuple direction = (pixel - origin).Normalized();

  return Ray(origin, direction);
}

Canvas Camera::Render(World w) {
  Canvas canvas = Canvas(width_, height_);

  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x){
      Ray r = RayForPixel(x, y);
      Color c = w.ColorAt(r);
      canvas.WritePixel(c, x, y);
    }
  }

  return canvas;
}
