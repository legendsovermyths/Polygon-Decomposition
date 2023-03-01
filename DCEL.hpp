#ifndef DCEL_HPP // include guard
#define DCEL_HPP
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Face;
/// @brief Represents the vertex of the polygon.
class Vertex
{
public:
    /// Index of the vertex
    int index;
    /// x-coordinate of the vertex
    double x;
    /// y-coordinate of the vertex
    double y;
};
/// @brief Represents a directed edge
class HalfEdge
{
public:
    /// @brief Vertex on which the edge is incident on
    Vertex *v;
    /// @brief Face on the right side of the directed edge
    Face *f;
    /// @brief The other half of the edge containing pointing to the Vertex this HalfEdge is incident on.
    HalfEdge *twin;
    /// @brief The next edge pointed by the directed edge.
    HalfEdge *next;
    /// @brief The previous edge this edge is pointing to.
    HalfEdge *prev;
};
class Face
{
public:
    HalfEdge *he;
    int id;
    Face(int n);
};
class Edge
{
public:
    pair<HalfEdge *, HalfEdge *> edge;
    Edge(HalfEdge *a, HalfEdge *b);
};

class DCEL
{
public:
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    vector<Face *> faces;
    int faceID = 2;
    int vertexID = 0;
    HalfEdge *addEdge(Vertex *&v1, Vertex *&v2, Face *&currFace);
    void removeEdge(HalfEdge *&h);
    void addVertex(double x, double y);
    void addFace(int id);
    void createPolygon(char *file);
    void outputPolygon(char *file);
    DCEL();
    ~DCEL();
    void print_();
};
#endif