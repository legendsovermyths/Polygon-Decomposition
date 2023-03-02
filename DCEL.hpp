#ifndef DCEL_HPP // include guard
#define DCEL_HPP
#include <iostream>
#include <set>
#include <vector>
using namespace std;

/// @brief Represents a face of the polygon
/// @note A face is a circular linked-list of half-edges that represents a polygon
class Face;

/// @brief Represents a vertex of the polygon.
/// @param index Index of the vertex
/// @param x x-coordingate of the vertex
/// @param y y-coordinate of the vertex
class Vertex {
  public:
    int index;
    double x;
    double y;
};

/// @brief Represents a directed edge in a 3D mesh.
///
/// A HalfEdge stores information about one half of an edge in the polygon. Each
/// edge in the polygon is represented by two HalfEdge objects, one for each
/// direction along the edge. The HalfEdge class stores information about the
/// vertex on which the edge is incident, the face on the right side of the
/// edge, and pointers to the other half of the edge and its neighboring edges.
class HalfEdge {
  public:
    /// @brief vertex on which the edge is incident.
    Vertex *v;

    /// @brief The face on the right side of the edge.
    Face *f;

    /// @brief The other half of the edge, pointing to the vertex opposite to
    /// this edge.
    HalfEdge *twin;

    /// @brief The next edge in the face, following this edge in a counterclockwise
    /// direction around the incident vertex.
    HalfEdge *next;

    /// @brief The previous edge in the face, preceding this edge in a counterclockwise
    /// direction around the incident vertex.
    HalfEdge *prev;
};

class Face {
  public:
    HalfEdge *he;
    int id;
    Face(int n);
};

class Edge {
  public:
    pair<HalfEdge *, HalfEdge *> edge;
    Edge(HalfEdge *a, HalfEdge *b);
};

/// @brief A data structure that represents a planar subdivision of a 2D surface.
///
/// @note DCEL (Doubly Connected Edge List) is a data structure commonly used to represent planar subdivisions of a 2D surface.
/// @note It stores information about the vertices, edges, and faces of the subdivision, along with their relationships to one another.
/// Specifically, each vertex stores a pointer to an incident edge, each edge stores pointers to its incident vertices, its twin edge (if any),
/// and the face on its right side, and each face stores a pointer to an incident edge on its boundary.
/// @note DCEL is often used in computational geometry algorithms, such as computing Voronoi diagrams and Delaunay triangulations.

class DCEL {
  public:
    /// @brief vector of Vertex objects containing all vertices in the polygon
    vector<Vertex *> vertices;

    /// @brief vector of Edge objects containing all edges in the pollygon
    vector<Edge *> edges;

    /// @brief vector of Face objects containing all the faces iin the decomposed polygon
    vector<Face *> faces;

    int faceID = 2;
    int vertexID = 0;

    /// @brief Adds a new edge between two vertices in a face, splitting the face into two.
    ///
    /// This function creates a new edge between two existing vertices in a given face and splits the face into two new faces.
    /// The new edge is returned, and its twin edge is also created and returned. The new edge starts at `v1` and ends at `v2`.
    /// The `currFace` parameter specifies the face that needs to be split by the added edge.
    ///
    /// @param v1 The starting vertex of the new edge.
    /// @param v2 The ending vertex of the new edge.
    /// @param currFace The face that needs to be split by the added edge.
    /// @return The HalfEdge starting at `v1` in the new edge.
    HalfEdge *addEdge(Vertex *&v1, Vertex *&v2, Face *&currFace);

    /// @brief Removes the half-edge h
    /// @param h  The half-edge that has to be removed
    void removeEdge(HalfEdge *&h);

    /// @brief Adds a new vertex to the vector of vertices with the specified coordinates.
    ///
    /// This function creates a new vertex with the specified `x` and `y` coordinates and adds it to the vector of vertices.
    ///
    /// @param x The x-coordinate of the new vertex.
    /// @param y The y-coordinate of the new vertex.
    void addVertex(double x, double y);

    /// @brief Adds a new face to the vector of faces with the specified ID.
    ///
    /// This function creates a new face with the specified `id` and adds it to the vector of faces.
    ///
    /// @param id The ID of the new face.
    void addFace(int id);

    /// @brief Creates a polygon from an input file with `n+1` lines, where `n` is the number of vertices in the polygon.
    ///
    /// This function reads an input file containing `n+1` lines, where `n` is the number of vertices in the polygon. The first line
    /// specifies the number of vertices `n`, while the next `n` lines contain two doubles, representing the x and y coordinates of each vertex.
    ///
    /// @param file The path to the input file containing the polygon data.
    void createPolygon(char *file);
    void outputPolygon(char *file);
    DCEL();
    ~DCEL();
    void print_();
};
#endif