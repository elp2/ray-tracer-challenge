#ifndef RTC_GUI_PREVIEW_WNDOW_H
#define RTC_GUI_PREVIEW_WNDOW_H

#include <vector>

class PreviewWindow {
 public:
  PreviewWindow();
  ~PreviewWindow() = default;

  bool Frame();

 private:
  float Progress() const;
};

#endif    // RTC_GUI_PREVIEW_WNDOW_H
