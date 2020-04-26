#include "scene/camera.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <thread>

#include "display/canvas.h"
#include "primitives/ray.h"
#include "scene/world.h"

Camera::Camera(const int width, const int height, const float field_of_view,
    const float aperature_radius, const float focal_length, const int rays_per_pixel) {
  assert(width > 0);
  assert(height > 0);
  assert(field_of_view < M_PI);
  assert(field_of_view > 0);

  width_ = width;
  assert(width_);
  height_ = height;
  field_of_view_ = field_of_view;

  aperature_radius_ = aperature_radius;
  aperature_radius_squared_ = pow(aperature_radius, 2.0);
  focal_length_ = focal_length;
  rays_per_pixel_ = rays_per_pixel;

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

const Tuple Camera::AperaturePoint() const {
  while (true) {
    float x = 2.0 * aperature_radius_ * rand() / (float)RAND_MAX - aperature_radius_;
    float y = 2.0 * aperature_radius_ * rand() / (float)RAND_MAX - aperature_radius_;

    if (pow(x, 2.0) + pow(y, 2.0) < aperature_radius_squared_);
      return Point(x, y, 0);
    }
    assert(false);
    return Point(0, 0, 0);
}

const std::vector<Ray> Camera::RaysForPixel(int x, int y) const {
  std::vector<Ray> rays;
  if (aperature_radius_ == 0.0) {
    // Simple point aperature.
    rays.push_back(RayForPixel(x, y, Point(0.0, 0.0, 0.0)));
    return rays;
  }

  for (int i = 0; i < rays_per_pixel_; ++i) {
    rays.push_back(RayForPixel(x, y, AperaturePoint()));
  }

  return rays;
}

const Ray Camera::RayForPixel(int x, int y, const Tuple &aperature_point) const {
  float x_offset = (x + 0.5) * pixel_size_;
  float y_offset = (y + 0.5) * pixel_size_;

  float world_x = half_width_ - x_offset;
  float world_y = half_height_ - y_offset;

  Tuple pixel = transform_.Inverse() * Point(world_x, world_y, -focal_length_);
  Tuple origin = transform_.Inverse() * aperature_point;
  Tuple direction = (pixel - origin).Normalized();

  return Ray(origin, direction);
}

Canvas Camera::Render(World w) {
  assert(transform_.Invertible() && "Impossible combination of up/from/to.");

  std::cout << "Rendering with " << std::thread::hardware_concurrency()
    << " threads." << std::endl;
  Canvas canvas = Canvas(width_, height_);
  canvas.set_report_render_progress(true);
  std::vector<std::thread> threads;
  for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
    std::thread thread (&Camera::RenderThread, this, &canvas, &w, i);
    threads.push_back(std::move(thread));
  }
  for (auto &thread : threads) {
    thread.join();
  }
  return canvas;
}

void Camera::RenderThread(Canvas *canvas, World *w, const int &mod) {
  for (int y = 0; y < height_; ++y) {
    if (y % std::thread::hardware_concurrency() != mod) {
      continue;
    }
    for (int x = 0; x < width_; ++x){
      std::vector<Ray> rays = RaysForPixel(x, y);
      Color c = BlackColor();
      for (auto r : rays) {
        c = c + w->ColorAt(r);
      }
      c = c * (1.0f / rays.size());
      canvas->WritePixel(c, x, y);
    }
  }
}
