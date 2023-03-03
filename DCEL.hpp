///@file dcel.hpp
///@brief Defines classes and functions for Doubly Connected Edge List (DCEL) data structure to represent planar subdivisions of a 2D surface.
///
/// A DCEL consists of a set of vertices, edges, and faces, with relationships between them, that can represent any planar graph or polygon.
/// It is commonly used in computational geometry algorithms, such as computing Voronoi diagrams and Delaunay triangulations.
///
#ifndef DCEL_HPP // include guard
#define DCEL_HPP
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// forward declarations
class Face;

/// @brief Represents a vertex of the polygon.
/// @param index Index of the vertex
/// @param x x-coordingate of the vertex
/// @param y y-coordinate of the vertex
class Vertex
{
public:
  int index;
  double x;
  double y;
};

/// @brief Represents a directed edge in a polygon.
///
/// A HalfEdge stores information about one half of an edge in the polygon. Each
/// edge in the polygon is represented by two HalfEdge objects, one for each
/// direction along the edge. The HalfEdge class stores information about the
/// vertex on which the edge is incident, the face on the right side of the
/// edge, and pointers to the other half of the edge and its neighboring edges.
class HalfEdge
{
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

/// @brief This class represents a Face object in the DCEL data structure.
///
/// It contains a HalfEdge pointer pointing to one of the HalfEdge objects in the Face.
/// Additionally, it has an id attribute to uniquely identify each Face object.
///
class Face
{
public:
  /// Pointer to the HalfEdge object in the Face.
  HalfEdge *he;
  /// Unique identifier for the Face object.
  int id;
  /// @brief Constructor for the Face class.
  /// @param n The unique identifier for the Face object.
  Face(int n);
};

/// @brief Represents an edge in the DCEL data structure as a pair of half edges.
///
/// An edge is defined as the line segment between two vertices in the polygon. It is represented by two HalfEdge objects
/// in the DCEL data structure, with one HalfEdge representing each directed end of the edge. The pair of HalfEdge objects
/// are stored as a pair in the edge member variable of the Edge class.
class Edge
{
public:
  pair<HalfEdge *, HalfEdge *> edge; ///< A pair of HalfEdge objects representing the two directed ends of the edge.
  /// @brief Constructs an Edge object with the specified HalfEdge objects representing the two ends of the edge.
  /// @param a The HalfEdge object representing one end of the edge.
  /// @param b The HalfEdge object representing the other end of the edge.
  Edge(HalfEdge *a, HalfEdge *b);
};

/// @brief A data structure that represents a planar subdivision of a 2D surface.
///
/// @note DCEL (Doubly Connected Edge List) is a data structure commonly used to represent planar subdivisions of a 2D surface.
/// @note It stores information about the vertices, edges, and faces of the subdivision, along with their relationships to one another.
/// Specifically, each vertex stores a pointer to an incident edge, each edge stores pointers to its incident vertices, its twin edge (if any),
/// and the face on its right side, and each face stores a pointer to an incident edge on its boundary.
/// @note DCEL is often used in computational geometry algorithms, such as computing Voronoi diagrams and Delaunay triangulations.
class DCEL
{
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

  /// @brief Writes the x and y coordinates of all vertices in each decomposed polygon to a file.
  ///
  /// This function writes the x and y coordinates of all vertices in each decomposed polygon to the
  /// specified output file. Each polygon is separated by the '$' symbol on a new line.
  ///
  /// @param file The path to the output file to which the polygon data will be written.

  void outputPolygon(char *file);

  /// @brief Default constructor for the DCEL class.
  ///
  /// This constructor initializes an empty DCEL data structure with no vertices, edges, or faces.
  DCEL();

  /// @brief Destructor for the DCEL class.
  ///
  /// This destructor frees the memory used by the DCEL data structure, including all vertices, edges, and faces.
  ~DCEL();

  /// @brief Prints DCEL to the console
  ///
  /// Prints the indices of the decomposed polygons face-wise
  ///
  void print_();
};
#endif