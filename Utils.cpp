#include "Utils.hpp"

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
bool orient(Vertex *v1, Vertex *v2, Vertex *v3) {
    return (v2->x - v1->x) * (v3->y - v1->y) - (v2->y - v1->y) * (v3->x - v1->x) <= 0;
}

/// @brief Returns a vector of pointers to the Vertex objects that are considered
/// notches within a given Face object.
/// 
/// Here, a notch is defined as a Vertex object in the Face object where two HalfEdge 
/// objects of the Face object meet at a reflex angle.
///
/// @param f Pointer to the Face object for which the notches need to be identified.
/// @return A vector of pointers to the Vertex objects representing the notches in the given face.
vector<Vertex *> getAllNotches(Face *f) {
    vector<Vertex *> v;
    HalfEdge *h = f->he;
    HalfEdge *t = h->next;
    if (orient(h->next->v, h->v, h->prev->v) == 0)
        v.push_back(h->v);
    while (h != t) {
        if (orient(t->next->v, t->v, t->prev->v) == 0)
            v.push_back(t->v);
        t = t->next;
    }

    return v;
}

bool isInside(Vertex *p1, Vertex *p2, Vertex *p3) {
    return orient(p1, p3, p2);
}