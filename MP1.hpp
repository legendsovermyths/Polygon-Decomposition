#ifndef MP1_HPP // include guard
#define MP1_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "DCEL.hpp"
#include "Rectangle.hpp"

class MP1
{
public:
    int st = 0;
    vector<Vertex *> L;
    vector<HalfEdge *> addedEdges;
    bool primeMP1(DCEL *polygon);
    void merge(DCEL *polygon);
};
#endif