#include "Utils.hpp"

bool orient(Vertex *v1, Vertex *v2, Vertex *v3)
{
    return (v2->x - v1->x) * (v3->y - v1->y) - (v2->y - v1->y) * (v3->x - v1->x) <= 0;
}
vector<Vertex *> getAllNotches(Face *f)
{
    vector<Vertex *> v;
    HalfEdge *h = f->he;
    HalfEdge *t = h->next;
    if (orient(h->next->v, h->v, h->prev->v) == 0)
        v.push_back(h->v);
    while (h != t)
    {
        if (orient(t->next->v, t->v, t->prev->v) == 0)
            v.push_back(t->v);
        t = t->next;
    }

    return v;
}
bool isInside(Vertex *p1, Vertex *p2, Vertex *p3)
{
    return orient(p1, p3, p2);
}