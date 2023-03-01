#ifndef Rectangle_HPP // include guard
#define Rectangle_HPP
#include <iostream>
#include "DCEL.hpp"
using namespace std;

/// @brief This class is used to make a Rectangle whose the edges are parallel to the coordinate
class Rectangle
{
public:
    double x1, x2, y1, y2; ///< x1 and y1 are the minimum x1 and y1 coordinate of the reactangle whereas x2 and y2 are the maximum coiordinates.
    Rectangle(vector<Vertex *> &L);
    bool isInside(Vertex *p);
};
#endif