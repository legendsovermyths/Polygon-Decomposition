#ifndef UTIL_HPP // include guard
#define UTIL_HPP
#include <iostream>
#include "DCEL.hpp"
#include "Line.hpp"
using namespace std;
/// @brief Determines whether a given vertex lies to the right or left of a
/// line defined by two other vertices
///
/// Given three vertices v1, v2, and v3, this function determines the orientation of v3
/// with respect to the line segment defined by v1 and v2
///
/// @param v1 The first vertex defining the line
/// @param v2 The second vertex defining the line
/// @param v3 The vertex to be checked
/// @return True if v3 lies to the right of or on the line defined by v1 and v2, false otherwise.
bool orient(Vertex *v1, Vertex *v2, Vertex *v3);
/// @brief Returns a vector of pointers to the Vertex objects that are considered
/// notches within a given Face object.
///
/// Here, a notch is defined as a Vertex object in the Face object where two HalfEdge
/// objects of the Face object meet at a reflex angle.
///
/// @param f Pointer to the Face object for which the notches need to be identified.
/// @return A vector of pointers to the Vertex objects representing the notches in the given face.
vector<Vertex *> getAllNotches(Face *f);
/// @brief Checks if two lines intersect
/// @param l1 first line
/// @param l2 second line
/// @return 1 if the lines intersect, 0 otherwise.
bool intersect(Line *l1, Line *l2);
/// @brief Checks if the Notch is inside the given polygon or not
/// @param L The polygon vertices sorted in cyclic order
/// @param notch The notch needs to be checked
/// @return 1 id the notch is inside 0 otherwise
bool isInside(vector<Vertex *> &L, Vertex *notch);
#endif
