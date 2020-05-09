#ifndef RTC_GUI_CAMERA_WNDOW_H
#define RTC_GUI_CAMERA_WNDOW_H

#include <vector>

class CameraWindow {
 public:
  CameraWindow();
  ~CameraWindow() = default;

  void Frame();

 private:
  float x_ = 0, y_ = 0, z_ = 0;
  float facing_x_ = 0, facing_y_ = 0, facing_z_ = 0;
  float up_x_ = 0, up_y_ = 0, up_z_ = 0;
};

#endif    // RTC_GUI_CAMERA_WNDOW_H
