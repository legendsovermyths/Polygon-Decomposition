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
///@note description
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
    bool primeMP1();

    ///@brief This function merges the separate convex polygons obtained from MP1 by removing the inessential,
    ///       duplicated diagonal edges.
    void merge();
};
#endif