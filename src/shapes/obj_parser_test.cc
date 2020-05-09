#include "gtest/gtest.h"

#include "shapes/obj_parser.h"
#include "shapes/smooth_triangle.h"
#include "shapes/triangle.h"

class ObjParserTest : public ::testing::Test {
 protected:
  ObjParserTest() {};
  ~ObjParserTest() {};
};

TEST(ObjParserTest, IgnoresGibberish) {
  auto ss = std::stringstream(std::string("This is \nA test.\nIt is only \na test."));
  ObjParser parser = ObjParser(ss);
  ASSERT_EQ(parser.DefaultGroup()->children()->size(), 0);
}

TEST(ObjParserTest, ParsesVertices) {
  auto s = "v -1 1 0\nv -1.0000 0.5000 0.0000\nv 1 0 0\nv 1 1 0\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);
  ASSERT_EQ(parser.Vertex(1), Point(-1, 1, 0));
  ASSERT_EQ(parser.Vertex(2), Point(-1, 0.5, 0));
  ASSERT_EQ(parser.Vertex(3), Point(1, 0, 0));
  ASSERT_EQ(parser.Vertex(4), Point(1, 1, 0));
}

TEST(ObjParserTest, ParsesTriangles) {
  auto s = "v -1 1 0\nv -1 0 0\nv 1 0 0\nv 1 1 0\n\nf 1 2 3\nf 1 3 4\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  Group *group = parser.DefaultGroup();
  ASSERT_EQ(group->children()->size(), 2);
  Triangle *t1 = (Triangle *)(*group->children())[0];
  Triangle *t2 = (Triangle *)(*group->children())[1];

  EXPECT_EQ(parser.Vertex(1), t1->p1());
  EXPECT_EQ(parser.Vertex(2), t1->p2());
  EXPECT_EQ(parser.Vertex(3), t1->p3());
  EXPECT_EQ(parser.Vertex(1), t2->p1());
  EXPECT_EQ(parser.Vertex(3), t2->p2());
  EXPECT_EQ(parser.Vertex(4), t2->p3());
}

TEST(ObjParserTest, ParsesPolygons) {
  auto s = "v -1 1 0\nv -1 0 0\nv 1 0 0\nv 1 1 0\nv 0 2 0\n\nf 1 2 3 4 5\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  Group *group = parser.DefaultGroup();
  ASSERT_EQ(group->children()->size(), 3);
  Triangle *t1 = (Triangle *)(*group->children())[0];
  Triangle *t2 = (Triangle *)(*group->children())[1];
  Triangle *t3 = (Triangle *)(*group->children())[2];

  EXPECT_EQ(parser.Vertex(1), t1->p1());
  EXPECT_EQ(parser.Vertex(2), t1->p2());
  EXPECT_EQ(parser.Vertex(3), t1->p3());
  EXPECT_EQ(parser.Vertex(1), t2->p1());
  EXPECT_EQ(parser.Vertex(3), t2->p2());
  EXPECT_EQ(parser.Vertex(4), t2->p3());
  EXPECT_EQ(parser.Vertex(1), t3->p1());
  EXPECT_EQ(parser.Vertex(4), t3->p2());
  EXPECT_EQ(parser.Vertex(5), t3->p3());
}

TEST(ObjParserTest, NamedGroups) {
  auto s = "v -1 1 0\nv -1 0 0\nv 1 0 0\nv 1 1 0\n\ng FirstGroup\nf 1 2 3\ng SecondGroup\nf 1 3 4\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  Group *first_group = parser.GroupNamed("FirstGroup");
  ASSERT_EQ(first_group->children()->size(), 1);
  Triangle *t1 = (Triangle *)(*first_group->children())[0];

  Group *second_group = parser.GroupNamed("SecondGroup");
  ASSERT_EQ(second_group->children()->size(), 1);
  Triangle *t2 = (Triangle *)(*second_group->children())[0];

  EXPECT_EQ(parser.Vertex(1), t1->p1());
  EXPECT_EQ(parser.Vertex(2), t1->p2());
  EXPECT_EQ(parser.Vertex(3), t1->p3());
  EXPECT_EQ(parser.Vertex(1), t2->p1());
  EXPECT_EQ(parser.Vertex(3), t2->p2());
  EXPECT_EQ(parser.Vertex(4), t2->p3());
}

TEST(ObjParserTest, SuperGroup) {
  auto s = "v -1 1 0\nv -1 0 0\nv 1 0 0\nv 1 1 0\n\ng FirstGroup\nf 1 2 3\ng SecondGroup\nf 1 3 4\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  Group *group = parser.SuperGroup();
  ASSERT_EQ(group->children()->size(), 2); // First, Second only (Default empty).
}

TEST(ObjParserTest, VertexNormals) {
  auto s = "vn 0 0 1\nvn 0.707 0 -0.707\nvn 1 2 3\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  EXPECT_EQ(parser.VertexNormal(1), Vector(0, 0, 1));
  EXPECT_EQ(parser.VertexNormal(2), Vector(0.707, 0, -0.707));
  EXPECT_EQ(parser.VertexNormal(3), Vector(1, 2, 3));
}

TEST(ObjParserTest, HandlesSpaces) {
  auto s = "vn 0   0 1\nvn 0.707 0   -0.707\nvn 1 2 3\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  EXPECT_EQ(parser.VertexNormal(1), Vector(0, 0, 1));
  EXPECT_EQ(parser.VertexNormal(2), Vector(0.707, 0, -0.707));
  EXPECT_EQ(parser.VertexNormal(3), Vector(1, 2, 3));
}


TEST(ObjParserTest, NormalVectorFaces) {
  auto s = "v 0 1 0\nv -1 0 0\nv 1 0 0\nvn -1 0 0\nvn 1 0 0\nvn 0 1 0\nf 1//3 2//1 3//2\nf 1/0/3 2/102/1 3/14/2\n";
  auto ss = std::stringstream(s);
  ObjParser parser = ObjParser(ss);

  Group *group = parser.DefaultGroup();
  ASSERT_EQ(group->children()->size(), 2);
  SmoothTriangle *t1 = (SmoothTriangle *)(*group->children())[0];

  EXPECT_EQ(t1->p1(), parser.Vertex(1));
  EXPECT_EQ(t1->p2(), parser.Vertex(2));
  EXPECT_EQ(t1->p3(), parser.Vertex(3));
  EXPECT_EQ(t1->n1(), parser.VertexNormal(3));
  EXPECT_EQ(t1->n2(), parser.VertexNormal(1));
  EXPECT_EQ(t1->n3(), parser.VertexNormal(2));
}
