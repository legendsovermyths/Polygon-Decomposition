#ifndef Rectangle_HPP // include guard
#define Rectangle_HPP
#include <iostream>
#include "DCEL.hpp"
using namespace std;

class Rectangle
{
public:
    double x1, x2, y1, y2;
    Rectangle(vector<Vertex *> &L);
    bool isInside(Vertex *p);
};
#endif