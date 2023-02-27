#include "MP1.hpp"
#include "Utils.hpp"
#include "DCEL.hpp"

bool MP1::primeMP1(DCEL *polygon)
{
    L.clear();
    vector<Vertex *> notches = getAllNotches(polygon->faces[1]);
    HalfEdge *begin = polygon->faces[1]->he;
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
    // for (int i = 0; i < L.size(); i++)
    //     cout << L[i]->index << " ";
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
                    Vertex *notch = notches[i];
                    if (notch != v_st && notch != v_end && r->isInside(notch) == 1 && isInside(v_st, v_end, notch) == 1)
                    {
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
    if (L.size() > 2)
        polygon->addEdge(L[0], L[L.size() - 1], polygon->faces[1]);
    return 0;
}
