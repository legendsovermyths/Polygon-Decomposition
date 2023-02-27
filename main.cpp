#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "DCEL.hpp"
#include "MP1.hpp"
#include "Rectangle.hpp"
using namespace std;

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    MP1 *mp1 = new MP1;
    int k = 100;
    while (k--)
        mp1->primeMP1(dcel);
    ;
    // dcel->print_();
    char out[] = "output.txt";
    dcel->outputPolygon(out);
}