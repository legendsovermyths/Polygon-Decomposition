#include <iostream>
#include <vector>
#include "DCEL.hpp"
#include "MP1.hpp"
#include "Rectangle.hpp"
using namespace std;

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    MP1 *mp1 = new MP1(dcel);
    int k1 = 100, k2 = 2;
    while (k1--)
        mp1->primeMP1();
    ;
    // while (k2--)
    //     mp1->merge();

    dcel->print_();
    char out[] = "output.txt";
    dcel->outputPolygon(out);
}