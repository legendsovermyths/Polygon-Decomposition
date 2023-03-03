/// @mainpage Polygon Decomposition
/// This project is about decomposing a simple polygon into convex polygons by creating diagonals and using DCEL data structure to store the polygon.
///
/// @file main.cpp
/// @brief This is the main source code of the project which utilizes APIs defined in this project to perform polygon decomposition.
#include "../include/DCEL.hpp"
#include "../include/Line.hpp"
#include "../include/Decompose.hpp"
#include "../include/Rectangle.hpp"
#include <chrono>
#include <iostream>
#include <vector>
using namespace std::chrono;
using namespace std;

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    Decompose *decompose = new Decompose(dcel);
    auto start = high_resolution_clock::now();
    while (decompose->primeDecompose() != 1)
        ;
    while (decompose->merge() != 0)
        ;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // dcel->print_();
    char out[] = "output.txt";
    dcel->outputPolygon(out);
    freopen("../results/time.txt", "w+", stdout);
    cout << duration.count();
    return 0;
}