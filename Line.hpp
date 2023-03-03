/// @file Line.hpp
/// @brief A class representing a line segment defined by two vertices.
#ifndef Line_HPP
#define Line_HPP
#include "DCEL.hpp"

/// @brief A class representing a line segment defined by two vertices.
class Line {
  public:
    /// Constructs a line segment from two vertices.
    /// @param p1 The first endpoint of the line segment.
    /// @param p2 The second endpoint of the line segment.
    Line(Vertex *p1, Vertex *p2);

    Vertex *v1, *v2; ///< The endpoints of the line segment.
};
#endif