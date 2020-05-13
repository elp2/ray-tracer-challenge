#ifndef RTC_GUI_PREVIEW_WNDOW_H
#define RTC_GUI_PREVIEW_WNDOW_H

#include <vector>

class Canvas;

class PreviewWindow {
 public:
  PreviewWindow(Canvas *canvas);
  ~PreviewWindow() = default;

  bool Frame();

 private:
  float Progress() const;
  Canvas *canvas_;
  unsigned int texture_id_;
};

#endif    // RTC_GUI_PREVIEW_WNDOW_H
