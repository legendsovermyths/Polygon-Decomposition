#include "Utils.hpp"
#include "Line.hpp"

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
bool intersect(Line *l1, Line *l2)
{
    int o1 = orient(l1->v1, l1->v2, l2->v1);
    int o2 = orient(l1->v1, l1->v2, l2->v2);
    int o3 = orient(l2->v1, l2->v2, l1->v1);
    int o4 = orient(l2->v1, l2->v2, l1->v2);
    if (o1 != o2 && o3 != o4)
        return 1;
    return 0;
}
bool isInside(vector<Vertex *> &L, Vertex *notch)
{
    Vertex *vl = new Vertex();
    vl->x = 10000;
    vl->y = notch->y;
    Line *l = new Line(notch, vl);
    int inter = 0, n = L.size();
    for (int i = 0; i < n; i++)
    {
        Line *edge = new Line(L[i], L[(i + 1) % n]);
        if (intersect(l, edge))
            inter++;
    }
    return inter & 1;
}