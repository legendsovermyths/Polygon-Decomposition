/// @file Line.cpp
/// @brief This file contains the implementation of the Line class which represents a line segment between two vertices.
#include "../include/Line.hpp"

Line::Line(Vertex *p1, Vertex *p2) {
    v1 = p1, v2 = p2;
}