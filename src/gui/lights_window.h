#ifndef RTC_GUI_LIGHTS_WNDOW_H
#define RTC_GUI_LIGHTS_WNDOW_H

#include "lights/point_light.h"

class LightsWindow {
 public:
  LightsWindow();
  ~LightsWindow() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Returns the point light on demand (e.g. on init).
  PointLight GetPointLight();

 private:
  float x_ = 0, y_ = 10.0, z_ = 0;
  float color_[3] = { 1.0, 1.0, 1.0 };
};

#endif    // RTC_GUI_LIGHTS_WNDOW_H
