#ifndef Line_HPP
#define Line_HPP
#include "DCEL.hpp"

class Line
{
public:
    Vertex *v1, *v2;
    Line(Vertex *p1, Vertex *p2);
};
#endif