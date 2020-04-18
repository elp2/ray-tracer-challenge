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

  Group *ToGroup() const;

  void AddFace(Triangle *face);
  const std::string name() const { return name_; };

 private:
  std::string name_;
  std::vector<Triangle *> faces_;
};

class ObjParser {
 public:
  ObjParser(std::stringstream &ss);
  ~ObjParser() = default;

  // Gets vertex (1 indexed).
  const Tuple Vertex(int v) const;

  // Returns the default group.
  Group *DefaultGroup() const;

  // Returns the group with the given name.
  Group *GroupNamed(std::string name) const;

  // Returns a group containing all groups parsed.
  Group *SuperGroup() const;

 private:
  void ParseLine(std::string line);
  void AddVertex(std::string coordinates);
  void AddFace(std::string vertices);
  void AddGroup(std::string name);

  std::vector<float> ParseFloats(std::string numbers);

  std::vector<Tuple> vertices_;

  // Groups. Current group is last group.
  std::vector<ObjGroup *> groups_;
};

#endif    // RTC_SHAPES_OBJ_PARSER_H
