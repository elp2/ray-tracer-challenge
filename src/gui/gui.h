#ifndef RTC_GUI_GUI_H
#define RTC_GUI_GUI_H

#include <vector>
#include "SDL.h"

class Camera;
class CameraWindow;
class PNGWriter;
class PreviewWindow;
class World;

class Gui {
 public:
  Gui();
  ~Gui() = default;

  void Show();

 private:
  void Cleanup() const;
  bool EventLoop();
  void Frame();
  void Update();

  Camera *camera_;
  PNGWriter *png_writer_;
  World *world_;

  PreviewWindow *preview_window_;
  CameraWindow *camera_window_;

  SDL_GLContext context_;
  SDL_Window *window_;
};

#endif    // RTC_GUI_GUI_H
