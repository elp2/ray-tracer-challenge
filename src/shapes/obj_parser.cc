#include "shapes/obj_parser.h"

#include <cassert>
#include <iostream>

void ObjGroup::AddFace(Triangle *face) {
  faces_.push_back(face);
}

Group *ObjGroup::ToGroup() const {
  Group *group = new Group();
  for (auto face : faces_) {
    group->AddChild(face);
  }
  return group;
}

ObjParser::ObjParser(std::stringstream &ss) {
  groups_.push_back(new ObjGroup(""));

  std::string line;
  while (std::getline(ss, line, '\n')) {
    ParseLine(line);
  }
}

void ObjParser::ParseLine(std::string line) {
  if (line.length() < 3) {
    return;
  }
  if (line.find("v") == 0) {
    AddVertex(line.substr(2));
  } else if (line.find("f") == 0) {
    AddFace(line.substr(2));
  } else if (line.find("g") == 0) {
    AddGroup(line.substr(2));
  } else {
    std::cout << "Unparseable: " << line << std::endl;
  }
}

std::vector<float> ObjParser::ParseFloats(std::string numbers) {
  std::vector<float> parsed;
  std::string num;
  std::stringstream ss = std::stringstream(numbers);
  while (std::getline(ss, num, ' ')) {
    parsed.push_back(stof(num));
  }
  return parsed;
}

void ObjParser::AddVertex(std::string coordinates) {
  std::vector<float> ps = ParseFloats(coordinates);
  assert(ps.size() == 3);
  Tuple v = Point(ps[0], ps[1], ps[2]);
  vertices_.push_back(v);
}

void ObjParser::AddFace(std::string vertices) {
  std::vector<float> vs = ParseFloats(vertices);
  assert(vs.size() >= 3);
  for (int i = 1; i < vs.size() - 1; ++i) {
    auto face = new Triangle(Vertex((int)vs[0]), Vertex((int)vs[i]), Vertex((int)vs[i + 1]));
    groups_[groups_.size() - 1]->AddFace(face);
  }
}

void ObjParser::AddGroup(std::string name) {
  auto group = new ObjGroup(name);
  groups_.push_back(group);
}

Group *ObjParser::DefaultGroup() const {
  return groups_[0]->ToGroup();
}

Group *ObjParser::SuperGroup() const {
  auto super_group = new Group();
  for (auto g : groups_) {
    auto ggroup = g->ToGroup();
    if (ggroup->size() > 0) {
      super_group->AddChild(g->ToGroup());
    }
  }
  return super_group;
}

Group *ObjParser::GroupNamed(std::string name) const {
  for (auto group : groups_) {
    if (name == group->name()) {
      return group->ToGroup();
    }
  }
  assert(false);
  return DefaultGroup();
}

const Tuple ObjParser::Vertex(int v) const {
  assert(v >= 1);
  int zero_indexed = v - 1;
  assert(zero_indexed < vertices_.size());
  return vertices_[zero_indexed];
}
