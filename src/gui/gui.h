#ifndef RTC_GUI_GUI_H
#define RTC_GUI_GUI_H

#include <vector>
#include "SDL.h"

class Camera;
class CameraWindow;
class Canvas;
class LightsWindow;
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
  Canvas *preview_canvas_;
  PNGWriter *png_writer_;
  World *world_;

  CameraWindow *camera_window_;
  LightsWindow *lights_window_;
  PreviewWindow *preview_window_;

  SDL_GLContext context_;
  SDL_Window *window_;
};

#endif    // RTC_GUI_GUI_H
