/// @mainpage Polygon Decomposition
/// This project is about decomposing a simple polygon into convex polygons by creating diagonals and using DCEL data structure to store the polygon.
///
/// @file main.cpp
/// @brief This is the main source code of the project which utilizes APIs defined in this project to perform polygon decomposition.
#include <iostream>
#include <vector>
#include "DCEL.hpp"
#include "MP1.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include <chrono>
using namespace std::chrono;
using namespace std;

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    MP1 *mp1 = new MP1(dcel);
    auto start = high_resolution_clock::now();
    while (mp1->primeMP1() != 1)
        ;
    while (mp1->merge() != 0)
        ;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // dcel->print_();
    char out[] = "output.txt";
    dcel->outputPolygon(out);
    freopen("time.txt", "w+", stdout);
    cout << duration.count();
    return 0;
}