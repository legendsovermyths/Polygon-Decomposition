#include "MP1.hpp"

bool is_right(pair<double, double> v1, pair<double, double> v2, pair<double, double> v3) {
    //  v1->v2->v3, returns 1 if v3 is on the
    // right of v1v2 else returns 0
    double x1 = v1.first, y1 = v1.second;
    double x2 = v2.first, y2 = v2.second;
    double x3 = v3.first, y3 = v3.second;
    double det = ((x2 - x1) * (y3 - y1)) - ((y2 - y1) * (x3 - x1));
    return (det < 0);
}

void MP1(vector<pair<double, double>> vertices) {
    // vertices vector of pair of coordinates read in CW order
    int m = 1, i = 0, length = vertices.size();
    pair<double, double> v1, v2;
    vector<pair<double, double>> L;
    L.push_back(vertices[i]);
    while (length > 3) {
        v1 = vertices[length - 1];
        v2 = vertices[i + 1];
        L.push_back(v2);
        i += 1;
        v2 = vertices[i + 1]; // ?? doubt, indexing is difficult
        while (is_right())

    }

    return;
}

int main() {
    // vector<pair<double, double>> vertices = input_polygon();
    // for (pair<double, double> p : vertices)
    //     // printing input vertices
    //     cout << "x = " << p.first << ", y = " << p.second << endl;
    pair<double, double> v1, v2, v3;
    v1 = make_pair(0, 0);
    v2 = make_pair(5, 5);
    v3 = make_pair(3, 3);
    cout << is_right(v1, v2, v3) << endl;
    return 0;
}