#ifndef RTC_GUI_OBJECT_VIEW_H
#define RTC_GUI_OBJECT_VIEW_H

#include <math.h>

class Cone;
class Cube;
class Cylinder;
class Group;
class MaterialView;
class Plane;
class Shape;
class Sphere;

enum ObjectType {
  ObjectType_Cone,
  ObjectType_Cube,
  ObjectType_Cylinder,
  ObjectType_Plane,
  ObjectType_Sphere,
  ObjectType_Teapot,
  ObjectType_Unknown,
};

class ObjectView {
 public:
  ObjectView();
  ~ObjectView() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Returns the shape here or nullptr if no valid shape.
  Shape *GetShape();

  // TODO: Callback to delete this.

 private:
  // TODO: Transform.
  // TODO: Callback Delgate.

  ObjectType type_ = ObjectType_Unknown;
  MaterialView *material_view_;

  Cone *GetCone();
  Cube *GetCube();
  Cylinder *GetCylinder();
  Sphere *GetSphere();
  Plane *GetPlane();
  Group *GetTeapot();

  // For cone and cylinder.
  float maximum_ = INFINITY;
  float minimum_ = -INFINITY;
  bool closed_ = false;
};

#endif    // RTC_GUI_OBJECT_VIEW_H
