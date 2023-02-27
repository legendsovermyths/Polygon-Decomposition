#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "DCEL.hpp"
#include "Utils.hpp"
#include "Rectangle.hpp"
using namespace std;

class MP1
{
public:
    vector<Vertex *> L;
    bool primeMP1(DCEL *polygon)
    {
        vector<Vertex *> notches = getAllNotches(polygon->faces[1]);
        srand(time(0));
        int k = rand() % 100;
        HalfEdge *begin = polygon->faces[1]->he;
        while (begin->v->index != 12)
            begin = begin->next;
        HalfEdge *next_begin = begin->next;
        Vertex *v1 = begin->v;
        Vertex *v2 = next_begin->v;
        cout << v1->index << endl;
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
        if (next_begin == begin)
        {
            return 1;
        }
        else if (L.size() < 2)
            return 1;
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
                    cout << v_end->index << endl;
                    Vertex *temp = v_st;
                    Rectangle *r = new Rectangle(L);
                    for (int i = 0; i < notches.size(); i++)
                    {
                        Vertex *notch = notches[i];
                        if (notch != v_st && notch != v_end && r->isInside(notch) == 1 && isInside(v_st, v_end, notch) == 1)
                        {
                            cout << notches[i]->index << endl;
                            L.pop_back();
                            break;
                        }
                    }
                }
                else
                    break;
            }
        }
        for (int i = 0; i < L.size(); i++)
            cout << L[i]->index << " ";
        cout << '\n';
        if (L.size() > 2)
            polygon->addEdge(L[0], L[L.size() - 1], polygon->faces[1]);
        return 0;
    }
};

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    MP1 *mp1 = new MP1;
    mp1->primeMP1(dcel);
    dcel->print_();
}