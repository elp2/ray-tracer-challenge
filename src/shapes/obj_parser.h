#ifndef RTC_SHAPES_OBJ_PARSER_H
#define RTC_SHAPES_OBJ_PARSER_H

#include "primitives/tuple.h"
#include "shapes/group.h"
#include "shapes/triangle.h"

#include <sstream>
#include <string>
#include <vector>


class ObjGroup {
 public:
  ObjGroup(std::string name) { name_ = name; };
  ~ObjGroup() = default;

  Group *ToGroup(Material material) const;

  void AddFace(Shape *face);
  const std::string name() const { return name_; };

 private:
  std::string name_;
  std::vector<Shape *> faces_;
};


struct FaceVertex {
  int vertex;
  int texture_vertex;
  int vertex_normal;
};

class ObjParser {
 public:
  ObjParser(std::stringstream &ss);
  ~ObjParser() = default;

  // Get vertex (1 indexed).
  const Tuple Vertex(int v) const;

  // Get vertex normal (1 indexed).
  const Tuple VertexNormal(int vn) const;

  // Returns the default group.
  Group *DefaultGroup() const;

  // Returns the group with the given name.
  Group *GroupNamed(std::string name) const;

  // Returns a group containing all groups parsed.
  Group *SuperGroup() const;

  void set_material(Material material) { material_ = material; };

 private:
  void ParseLine(std::string line);
  const std::vector<FaceVertex> ParseFaceVertices(std::string vertices) const;
  const std::vector<float> ParseFloats(std::string numbers) const;

  void AddVertex(std::string coordinates);
  void AddVertexNormal(std::string vector);
  void AddFace(std::string vertices);
  void AddGroup(std::string name);


  std::vector<Tuple> vertices_;
  std::vector<Tuple> vertex_normals_;

  // Groups. Current group is last group.
  std::vector<ObjGroup *> groups_;

  Material material_;
};

#endif    // RTC_SHAPES_OBJ_PARSER_H
