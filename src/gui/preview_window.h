#ifndef RTC_GUI_PREVIEW_WNDOW_H
#define RTC_GUI_PREVIEW_WNDOW_H

#include <vector>

class PreviewWindow {
 public:
  PreviewWindow();
  ~PreviewWindow() = default;

  void Frame();

 private:
  const float Progress() const;
};

#endif    // RTC_GUI_PREVIEW_WNDOW_H
