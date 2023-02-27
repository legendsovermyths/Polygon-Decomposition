#ifndef UTIL_HPP // include guard
#define UTIL_HPP
#include <iostream>
#include "DCEL.hpp"
using namespace std;

bool orient(Vertex *v1, Vertex *v2, Vertex *v3);
vector<Vertex *> getAllNotches(Face *f);
bool isInside(Vertex *p1, Vertex *p2, Vertex *p3);
#endif
