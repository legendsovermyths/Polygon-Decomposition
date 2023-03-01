#ifndef DCEL_HPP // include guard
#define DCEL_HPP
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Face;
class Vertex
{
public:
    int index;
    double x;
    double y;
};
class HalfEdge
{
public:
    Vertex *v;
    Face *f;
    HalfEdge *twin;
    HalfEdge *next;
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

/*!@brief Doubly connected edge list is a  data structure
 *
 */
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