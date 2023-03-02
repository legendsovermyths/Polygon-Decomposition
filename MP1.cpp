#include "MP1.hpp"
#include "Utils.hpp"
#include "DCEL.hpp"

///@brief Finds all notches and prints them.
///@param dcel Input polygon as a doubly connected edge list
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

///@brief Main MP1 algorithm to decompose input polygon
///@return 1 if polygon has only 1 edge, 0 otherwise
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
                    for (int b = 0; b < L.size(); b++)
                    {
                        if (notch == L[b])
                            contain = 1;
                    }
                    if (contain == 0 && r->isInside(notch) == 1 && isInside(v_st, v_end, notch) == 1)
                    {
                        cout << notch->index << '\n';
                        L.pop_back();
                        break;
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

///@brief Merging algorithm to remove inessential diagonals
///@return void
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
        cout << v1_prev->index << " " << v1->index << " " << v1_next->index << endl;
        cout << v2_prev->index << " " << v2->index << " " << v2_next->index << endl;
        cout << endl;
        if (orient(v1_prev, v1, v1_next) == 1 && orient(v2_prev, v2, v2_next) == 1)
        {
            polygon->removeEdge(addedEdges[i]);
        }
        else
            e.push_back(addedEdges[i]);
    }
    addedEdges = e;
}
