#ifndef MP1_HPP // include guard
#define MP1_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "DCEL.hpp"
#include "Rectangle.hpp"
#define EXTERNAL_FACE 0
#define WORKING_FACE 1

class MP1
{
public:
    int st = 0;
    DCEL *polygon;
    vector<Vertex *> L;
    vector<HalfEdge *> addedEdges;
    vector<Vertex *> notches;
    MP1(DCEL *&dcel);
    bool primeMP1();
    void merge();
};
#endif