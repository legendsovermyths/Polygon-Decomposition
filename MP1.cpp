///@file MP1.cpp
///@brief Implementation of the MP1 algorithm for polygon triangulation.
///
/// The MP1 algorithm is a variant of the ear-clipping method that is used to decompose a polygon into a set of triangles.
/// This algorithm is capable of handling polygons with holes and is useful for a variety of applications in computer graphics and computational geometry.
/// The MP1 algorithm works by finding a sequence of vertices that form a simple polygon, and then removing inessential diagonals until the polygon is completely triangulated.
///
#include "MP1.hpp"
#include "Utils.hpp"
#include "DCEL.hpp"

MP1::MP1(DCEL *&dcel)
{
    notches = getAllNotches(dcel->faces[EXTERNAL_FACE]);
    polygon = dcel;
    for (int i = 0; i < notches.size(); i++)
    {
        cout << notches[i]->index << " ";
    }
    cout << '\n';
}

bool MP1::primeMP1()
{
    L.clear();
    HalfEdge *begin = polygon->faces[WORKING_FACE]->he;
    int k = st++;
    while (k--)
        begin = begin->next;
    HalfEdge *next_begin = begin->next;
    Vertex *v1 = begin->v;
    Vertex *v2 = next_begin->v;
    L.push_back(v1);
    L.push_back(v2);
    Vertex *v_m1 = v1;
    Vertex *vi = v2;
    Vertex *vi_p = next_begin->next->v;
    while (next_begin != begin)
    {
        if (orient(v_m1, vi, vi_p) == 1 && orient(vi, vi_p, v1) == 1 && orient(vi_p, v1, v2) == 1)
        {
            L.push_back(vi_p);
        }
        else
            break;
        v_m1 = vi;
        vi = vi_p;
        next_begin = next_begin->next;
        vi_p = next_begin->next->v;
    }
    for (int i = 0; i < L.size(); i++)
    {
        cout << L[i]->index << " ";
    }
    cout << '\n';
    if (next_begin == begin)
    {
        return 1;
    }
    else if (L.size() <= 2)
        return 0;
    else
    {
        int prev = 0;
        while (L.size() > 2)
        {
            if (prev != L.size())
            {
                prev = L.size();
                Vertex *v_st = L[0];
                Vertex *v_end = L[L.size() - 1];
                Vertex *temp = v_st;
                Rectangle *r = new Rectangle(L);
                for (int i = 0; i < notches.size(); i++)
                {
                    int contain = 0;
                    Vertex *notch = notches[i];
                    if (r->isInside(notch))
                    {
                        for (int b = 0; b < L.size(); b++)
                        {
                            if (notch == L[b])
                                contain = 1;
                        }
                        if (contain == 0 && isInside(L, notch) == 1)
                        {
                            L.pop_back();
                            break;
                        }
                    }
                }
            }
            else
                break;
        }
    }

    // cout << '\n'
    //      << endl;
    for (int i = 0; i < L.size(); i++)
    {
        cout << L[i]->index << " ";
    }
    cout << '\n'
         << endl;
    ;
    if (L.size() > 2)
    {
        HalfEdge *h = polygon->addEdge(L[0], L[L.size() - 1], polygon->faces[1]);
        addedEdges.push_back(h);
    }
    return 0;
}

void MP1::merge()
{
    vector<HalfEdge *> e;
    for (int i = 0; i < addedEdges.size(); i++)
    {
        Vertex *v1 = addedEdges[i]->v;
        Vertex *v1_next = addedEdges[i]->twin->next->next->v;
        Vertex *v1_prev = addedEdges[i]->prev->v;
        Vertex *v2 = addedEdges[i]->twin->v;
        Vertex *v2_next = addedEdges[i]->next->next->v;
        Vertex *v2_prev = addedEdges[i]->twin->prev->v;
        if (orient(v1_prev, v1, v1_next) == 1 && orient(v2_prev, v2, v2_next) == 1)
        {
            polygon->removeEdge(addedEdges[i]);
        }
        else
            e.push_back(addedEdges[i]);
    }
    addedEdges = e;
}
