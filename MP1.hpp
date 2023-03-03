///@file MP1.hpp
///@brief Algorithm to decompose a simple polygon into a number of convex polygons.
#ifndef MP1_HPP // include guard
#define MP1_HPP
#include "DCEL.hpp"
#include "Rectangle.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#define EXTERNAL_FACE 0
#define WORKING_FACE 1

///@brief Algorithm to decompose a simple polygon into a number of convex polygons.
///
/// The MP1 class constructor takes a doubly connected edge list (DCEL) as input and initializes the notches vector
/// by calling the getAllNotches() function on the external face of the input polygon. It then initializes the polygon
/// data member and prints out the indices of all the notches in the input polygon.
///
/// The primeMP1() function implements the main MP1 algorithm. It first initializes an empty list L, and then adds the
/// first two vertices of the polygon to L. It then iterates over the remaining vertices of the polygon and adds them to L if
/// they form a "convex corner" with the previous two vertices. If the polygon has only one edge, it returns true.
/// If L has two or fewer vertices, it returns false. Otherwise, it repeatedly removes "inessential vertices" from L until
/// L has only three vertices left. An inessential vertex is a vertex that does not affect the monotonicity of the polygon. 
/// This is done by creating a rectangle that bounds the current chain of vertices in L, and then checking if any notches are 
/// inside the rectangle but outside the chain of vertices. If such a notch is found, the vertex of L that is farthest from 
/// the segment connecting the notch to the opposite vertex of the rectangle is removed from L. Finally, if L has more 
/// than three vertices, an edge is added from the first to the last vertex of L, and the function returns false.
///
/// The merge() function implements the merging algorithm to remove inessential diagonals. It iterates over all the edges that 
////were added to the polygon in the previous step and removes them if they are not "essential" diagonals. An essential diagonal 
/// is a diagonal that connects two vertices that form a convex corner with each other.
///
class MP1 {
  public:
    ///@brief
    int st = 0;

    ///@brief A Double connected edge list data structure to store all the information of the main polygon
    DCEL *polygon;

    ///@brief vector of Vertex objects containing all vertices of the next future convex polygon of the partition
    vector<Vertex *> L;

    ///@brief vector of HalfEdge objects containing half edges of all the added diagonal partition edges in the polygon
    vector<HalfEdge *> addedEdges;

    ///@brief vector of Vertex objects containing all notches of the input polygon
    vector<Vertex *> notches;

    ///@brief This function initializes polygon and finds all the notches of the input polygon.
    ///@param dcel Input polygon as a doubly connected edge list
    MP1(DCEL *&dcel);

    ///@brief This function implements the MP1 algorithm as given in the paper.
    ///       It decomposes the input polygon into a number of separate convex polygons.
    ///@return True if polygon has only 1 edge, False otherwise
    bool primeMP1();

    ///@brief This function merges the separate convex polygons obtained from MP1 by removing the inessential,
    ///       duplicated diagonal edges.
    void merge();
};
#endif