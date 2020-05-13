#ifndef RTC_GUI_CAMERA_WNDOW_H
#define RTC_GUI_CAMERA_WNDOW_H

#include <math.h>
#include <vector>

class Camera;
class Canvas;

class CameraWindow {
 public:
  CameraWindow(Canvas *canvas_);
  ~CameraWindow() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Returns the camera on demand (e.g. on init).
  Camera *GetCamera();

 private:
  float x_ = 5, y_ = 5, z_ = 5;
  float to_x_ = 0, to_y_ = 0, to_z_ = 0;
  float up_x_ = 0, up_y_ = 1, up_z_ = 0;
  float field_of_view_ = M_PI / 4.0;
  float aperature_radius_ = 0;
  float focal_length_ = 0.0;
  int rays_per_pixel_ = 1;
  Canvas *canvas_;
};

#endif    // RTC_GUI_CAMERA_WNDOW_H
