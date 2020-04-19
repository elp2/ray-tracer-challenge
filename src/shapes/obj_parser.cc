#include "shapes/obj_parser.h"

#include "shapes/triangle.h"
#include "shapes/smooth_triangle.h"

#include <cassert>
#include <iostream>

void ObjGroup::AddFace(Shape *face) {
  faces_.push_back(face);
}

Group *ObjGroup::ToGroup(Material material) const {
  Group *group = new Group(material);
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
  if (line.find("v ") == 0) {
    AddVertex(line.substr(2));
  } else if (line.find("f ") == 0) {
    AddFace(line.substr(2));
  } else if (line.find("g ") == 0) {
    AddGroup(line.substr(2));
  } else if (line.find("vn ") == 0) {
    AddVertexNormal(line.substr(3));
  } else {
    std::cout << "Unparseable: " << line << std::endl;
  }
}

const std::vector<float> ObjParser::ParseFloats(std::string numbers) const {
  std::vector<float> parsed;
  std::string num;
  std::stringstream ss = std::stringstream(numbers);
  while (std::getline(ss, num, ' ')) {
    if (num.size()) {
      parsed.push_back(stof(num));
    }
  }
  return parsed;
}

void ObjParser::AddVertex(std::string coordinates) {
  std::vector<float> ps = ParseFloats(coordinates);
  assert(ps.size() == 3);
  Tuple v = Point(ps[0], ps[1], ps[2]);
  vertices_.push_back(v);
}

const std::vector<FaceVertex> ObjParser::ParseFaceVertices(std::string vertices) const {
  std::vector<FaceVertex> face_vertices;
  std::string vertex_string;
  std::stringstream spaces = std::stringstream(vertices);
  while (std::getline(spaces, vertex_string, ' ')) {
    std::string fv;
    std::stringstream fvss = std::stringstream(vertex_string);
    int vertex = 0;
    int texture_vertex = 0;
    int vertex_normal = 0;
    if (std::getline(fvss, fv, '/')) {
      if (fv.length()) {
        vertex = stoi(fv);
      }
    }
    if (std::getline(fvss, fv, '/')) {
      if (fv.length()) {
        texture_vertex = stoi(fv);
      }
    }
    if (std::getline(fvss, fv, '/')) {
      if (fv.length()) {
       vertex_normal = stoi(fv);
      }
    }
    struct FaceVertex face_vertex = { vertex, texture_vertex, vertex_normal };
    face_vertices.push_back(face_vertex);
  }
  return face_vertices;
}

void ObjParser::AddFace(std::string vertices) {
  std::vector<FaceVertex> fv = ParseFaceVertices(vertices);
  assert(fv.size() >= 3);
  for (int i = 1; i < fv.size() - 1; ++i) {
    int vn0 = fv[0].vertex_normal;
    int vni = fv[i].vertex_normal;
    int vni1 = fv[i + 1].vertex_normal;
    if (vn0 == 0 && vni == 0 && vni1 ==0) {
      auto face = new Triangle(Vertex(fv[0].vertex), Vertex(fv[i].vertex), Vertex(fv[i + 1].vertex));
      groups_[groups_.size() - 1]->AddFace(face);
    } else {
      auto face = new SmoothTriangle(Vertex(fv[0].vertex), Vertex(fv[i].vertex), Vertex(fv[i + 1].vertex),
          VertexNormal(vn0), VertexNormal(vni), VertexNormal(vni1));
      groups_[groups_.size() - 1]->AddFace(face);
    }
  }
}

void ObjParser::AddGroup(std::string name) {
  auto group = new ObjGroup(name);
  groups_.push_back(group);
}

void ObjParser::AddVertexNormal(std::string vector) {
  std::vector<float> ps = ParseFloats(vector);
  assert(ps.size() == 3);
  Tuple v = Vector(ps[0], ps[1], ps[2]);
  vertex_normals_.push_back(v);
}

const Tuple ObjParser::VertexNormal(int vn) const {
  assert(vn >= 1);
  int idx = vn - 1;
  assert(idx < vertex_normals_.size());
  return vertex_normals_[idx];
}

Group *ObjParser::DefaultGroup() const {
  return groups_[0]->ToGroup(material_);
}

Group *ObjParser::SuperGroup() const {
  auto super_group = new Group(material_);
  for (auto g : groups_) {
    auto ggroup = g->ToGroup(material_);
    if (ggroup->size() > 0) {
      super_group->AddChild(g->ToGroup(material_));
    }
  }
  return super_group;
}

Group *ObjParser::GroupNamed(std::string name) const {
  for (auto group : groups_) {
    if (name == group->name()) {
      return group->ToGroup(material_);
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
