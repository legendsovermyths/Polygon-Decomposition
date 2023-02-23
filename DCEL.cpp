#include <iostream>
#include <vector>
using namespace std;
class Face;
class Vertex
{
public:
    // int index;
    double x;
    double y;
    HalfEdge *incident;
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
};
class Edge
{
public:
    HalfEdge *he;
};
class DCEL
{
public:
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    vector<Face *> faces;
    DCEL(){};
    void addEdge(Vertex *v1, Vertex *v2)
    {
        // TODO
    }
    void addVertex(double x, double y)
    {
        Vertex *v = new Vertex();
        v->x = x;
        v->y = y;
        vertices.push_back(v);
    }
    void createPolygon(char *file)
    {
        freopen(file, "r", stdin);
        int n;
        cin >> n;
        double x, y;
        while (n--)
        {
            cin >> x >> y;
            addVertex(x, y);
        }
        for (int i = 0; i < vertices.size(); i++)
        {
        }
    }
    ~DCEL()
    {
        vertices.clear();
        edges.clear();
        faces.clear();
    }
};
