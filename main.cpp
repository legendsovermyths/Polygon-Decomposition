/**
 *@mainpage  Polygon Decomposition
 *A project on Simple Polygon decomposition. A simple polygon is decomposed to convex polygon by making diagonals and using DCEL to store the Polygon.
 *
 *
 */

/**
 *@file         main.cpp
 *@brief        This is the main source code of the project. It uses API defined in this project to decompose the polygon.
 */
#include <iostream>
#include <vector>
#include "DCEL.hpp"
#include "MP1.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
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
    while (k2--)
        mp1->merge();

    dcel->print_();
    char out[] = "output.txt";
    dcel->outputPolygon(out);
}