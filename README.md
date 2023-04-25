# Polygon Decomposition

This project is about decomposing a simple polygon into convex polygons
by creating diagonals and using the DCEL data structure to
store the polygon using the algorithm described in this [paper](https://github.com/bharathvariar/Polygon-Decomposition/blob/main/Algorithms%20for%20the%20decomposition%20of%20a%20polygon%20into%20convex.pdf)

## 1. Double-Connected Edge List (DCEL):

DCEL (Doubly Connected Edge List) is a data structure commonly used to represent planar subdivisions of a
2D surface.

It stores information about the vertices, edges, and faces of the subdivision, along with their relationships to
one another. Specifically, each vertex stores a pointer to an incident edge, each edge stores pointers to its
incident vertices, its twin edge (if any), and the face on its right side, and each face stores a pointer to an
incident edge on its boundary.

DCEL is often used in computational geometry algorithms, such as computing Voronoi diagrams and Delaunay
triangulations.

### 1.1 HalfEdge:

A HalfEdge stores information about one half of an edge in the polygon. Each edge in the polygon is represented
by two HalfEdge objects, one for each direction along the edge. The HalfEdge class stores information about the
vertex on which the edge is incident, the face on the right side of the edge, and pointers to the other half of the edge
and its neighboring edges.

### 1.2 Edge

An edge in a DCEL data structure is defined as the line segment between two vertices in the polygon. It is represented by two HalfEdge
objects, with one HalfEdge representing each directed end of the edge. The pair of HalfEdge objects are stored as a pair in the edge member
variable of the Edge class.

### 1.3 Face:

It contains a HalfEdge pointer pointing to one of the HalfEdge objects in the Face. Additionally, it has an id attribute
to uniquely identify each Face object.

## 2. The Decompose Algorithm:

The Decompose class constructor takes a doubly connected edge list (DCEL) as input and initializes the notches vector
by calling the getAllNotches() function on the external face of the input polygon. It then initializes the polygon data
member and prints out the indices of all the notches in the input polygon.

The primeDecompose() function implements the main Decompose algorithm. It first initializes an empty list L, and then adds the
first two vertices of the polygon to L. It then iterates over the remaining vertices of the polygon and adds them to L
if they form a "convex corner" with the previous two vertices. If the polygon has only one edge, it returns true. If L
has two or fewer vertices, it returns false. Otherwise, it repeatedly removes "inessential vertices" from L until L has
only three vertices left. An inessential vertex is a vertex that does not affect the monotonicity of the polygon. This
is done by creating a rectangle that bounds the current chain of vertices in L, and then checking if any notches are
inside the rectangle but outside the chain of vertices. If such a notch is found, the vertex of L that is farthest from
the segment connecting the notch to the opposite vertex of the rectangle is removed from L. Finally, if L has more
than three vertices, an edge is added from the first to the last vertex of L, and the function returns false.

The merge() function implements the merging algorithm to remove inessential diagonals. It iterates over all the
edges that were added to the polygon in the previous step and removes them if they are not "essential" diagonals. Where, An essential
diagonal is a diagonal that connects two vertices that form a convex corner with each other.
