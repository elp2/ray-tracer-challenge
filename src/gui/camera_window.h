#ifndef RTC_GUI_CAMERA_WNDOW_H
#define RTC_GUI_CAMERA_WNDOW_H

#include <math.h>
#include <vector>

class Camera;

class CameraWindow {
 public:
  CameraWindow();
  ~CameraWindow() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Returns the camera on demand (e.g. on init).
  Camera *GetCamera();

 private:
  float x_ = 0, y_ = 0, z_ = 0;
  float facing_x_ = 0, facing_y_ = 0, facing_z_ = 0;
  float up_x_ = 0, up_y_ = 0, up_z_ = 0;
  float field_of_view_ = M_PI / 4.0;
  float aperature_radius_ = 0;
  float focal_length_ = 0.0;
  int rays_per_pixel_ = 1;
};

#endif    // RTC_GUI_CAMERA_WNDOW_H
