/// @file rectangle.cpp
/// @brief Implementation file for the Rectangle class, used for creating a rectangular boundary around a set of vertices.
#include "Rectangle.hpp"
#include "DCEL.hpp"

Rectangle::Rectangle(vector<Vertex *> &L)
{
    x1 = -1000, y1 = -1000, x2 = 1000, y2 = 1000;
    for (int i = 0; i < L.size(); i++)
    {
        x1 = max(x1, L[i]->x);
        x2 = min(x2, L[i]->x);
        y1 = max(y1, L[i]->y);
        y2 = min(y2, L[i]->y);
    }
}

bool Rectangle::isInside(Vertex *p)
{
    if (x2 <= p->x && x1 >= p->x && y2 <= p->y && y1 >= p->y)
        return true;
    else
        return false;
}