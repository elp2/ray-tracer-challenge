#ifndef RTC_SCENE_CAMERA_H
#define RTC_SCENE_CAMERA_H

#include <vector>

#include "primitives/color.h"
#include "primitives/matrix.h"

class Canvas;
class Ray;
class World;

class Camera {
 public:
  Camera(const int width, const int height, const float field_of_view,
      const float aperature_radius, const float focal_length, const int rays_per_pixel,
      bool supersample);

  Camera(const int width, const int height, const float field_of_view) :
      Camera(width, height, field_of_view, 0.0, 1.0, 1, false) {};

  Camera(const int width, const int height, const float field_of_view, bool supersample) :
      Camera(width, height, field_of_view, 0.0, 1.0, 1, supersample) {};

  ~Camera() = default;

  int width() { return width_; };
  int height() { return height_; };
  float field_of_view() { return field_of_view_; };
  float pixel_size() { return pixel_size_; };
  Matrix transform() { return transform_; };

  const Tuple AperaturePoint() const;

  const std::vector<Ray> RaysForPixel(float x, float y) const;
  const Ray RayForPixel(float x, float y, const Tuple &aperature_point) const;
  void RenderPixel(Canvas *canvas, World *w, int x, int y) const;
  const Color SubPixelColor(World *w, float x, float y) const;

  void set_transform(Matrix transform) { transform_ = transform; };

  // Cancels the rendering, preventing further writes from happening.
  void Cancel() { cancelled_ = true; };

  Canvas *Render(World w);

  void set_canvas(Canvas *canvas) { canvas_ = canvas; };

 private:
  int width_ = 0;
  int height_ = 0;
  float field_of_view_ = 0.0;
  Matrix transform_ = IdentityMatrix(4);
  float pixel_size_ = 0.0;
  float half_width_ = 0.0;
  float half_height_ = 0.0;
  float focal_length_ = 1.0;
  float aperature_radius_ = 0.0;
  float aperature_radius_squared_ = 0.0;
  int rays_per_pixel_ = 0;
  bool cancelled_ = false;
  Canvas *canvas_ = nullptr;
  bool supersample_ = false;

  void RenderThread(Canvas *canvas, World *w, const int &mod);
};

#endif    // RTC_SCENE_CAMERA_H
