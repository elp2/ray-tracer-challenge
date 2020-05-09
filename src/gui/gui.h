#ifndef RTC_GUI_GUI_H
#define RTC_GUI_GUI_H

#include <vector>
#include "SDL.h"

class CameraWindow;
class PreviewWindow;

class Gui {
 public:
  Gui();
  ~Gui() = default;

  void Show();

 private:
  void Cleanup() const;
  bool EventLoop();
  void Frame();

  PreviewWindow *preview_window_;
  CameraWindow *camera_window_;

  SDL_GLContext context_;
  SDL_Window *window_;
};

#endif    // RTC_GUI_GUI_H
