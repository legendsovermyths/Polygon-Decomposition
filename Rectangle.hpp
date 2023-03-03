///@file Rectangle.hpp
///@brief Declaration of Rectangle class for representing a rectangle whose 
///edges are parallel to the coordinate axes
#ifndef Rectangle_HPP // include guard
#define Rectangle_HPP
#include <iostream>
#include "DCEL.hpp"
using namespace std;

///@brief This class is used to make a Rectangle whose the edges are parallel to the coordinate axis 
class Rectangle
{
public:
    ///@brief x1 and y1 are the minimum x and y coordinates of the reactangle whereas x2 and y2 are the maximum coordinates.
    double x1, x2, y1, y2; 
    Rectangle(vector<Vertex *> &L);
    bool isInside(Vertex *p);
};

/// @brief A class for representing a rectangle whose edges are parallel to the coordinate axes.
/// @details The class stores the minimum and maximum coordinates along the x and y axes of the polygon.
/// The coordinates are specified using the parameters x1, y1, x2, and y2. The class also has a method isInside()
/// that takes a Vertex pointer and returns true if the vertex lies inside the rectangle, and false otherwise.
class Rectangle {
  public:
    /// The minimum and maximum x and y coordinates of the rectangle.
    double x1, x2, y1, y2;
    /// @brief Constructs a Rectangle object from a vector of Vertex pointers.
    /// The Rectangle is created such that it encloses all the vertices in the input vector.
    /// @param L A vector of Vertex pointers representing the vertices that the Rectangle must enclose.
    Rectangle(vector<Vertex *> &L);
    /// @brief Checks whether a given Vertex lies inside the Rectangle.
    /// @param p A pointer to the Vertex to check.
    /// @return Returns true if the Vertex lies inside the Rectangle, false otherwise.
    bool isInside(Vertex *p);
};
#endif