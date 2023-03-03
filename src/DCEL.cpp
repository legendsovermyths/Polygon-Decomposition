///@file DCEL.cpp
///@brief Implementation of the DCEL class
#include "../include/DCEL.hpp"

Face::Face(int n)
{
    id = n;
}

Edge::Edge(HalfEdge *a, HalfEdge *b)
{
    edge.first = a;
    edge.second = b;
}

DCEL::DCEL()
{
    faces.push_back(new Face(0));
}

HalfEdge *DCEL::addEdge(Vertex *&v1, Vertex *&v2, Face *&currFace)
{
    int fid = currFace->id;
    HalfEdge *fromV1 = new HalfEdge();
    HalfEdge *fromV2 = new HalfEdge();
    HalfEdge *halfV1, *halfV2;
    HalfEdge *traverse = currFace->he;
    HalfEdge *travel = traverse->next;
    if (traverse->v == v1)
        halfV1 = *&traverse;
    if (traverse->v == v2)
        halfV2 = *&traverse;
    while (traverse != travel)
    {
        if (travel->v == v1)
            halfV1 = *&travel;
        if (travel->v == v2)
            halfV2 = *&travel;
        travel = travel->next;
    }
    HalfEdge *halfV1_prev = *&halfV1->prev;
    HalfEdge *halfV2_prev = *&halfV2->prev;
    halfV1->prev = fromV2;
    halfV2_prev->next = fromV2;
    fromV2->prev = halfV2_prev;
    fromV2->next = halfV1;
    halfV2->prev = fromV1;
    halfV1_prev->next = fromV1;
    fromV1->next = halfV2;
    fromV1->prev = halfV1_prev;
    fromV1->twin = fromV2;
    fromV2->twin = fromV1;
    Face *face = new Face(faceID++);
    HalfEdge *temp = fromV2;
    fromV2->f = face;
    fromV1->f = currFace;
    fromV1->v = v1;
    fromV2->v = v2;
    face->he = fromV2;
    currFace->he = fromV1;
    edges.push_back(new Edge(fromV1, fromV2));
    temp = temp->next;
    while (temp != fromV2)
    {
        HalfEdge *temp2 = &*temp;
        temp2->f = face;
        temp = temp->next;
    }
    faces.push_back(face);
    return fromV1;
    // TODO: implement joining  logic
}

void DCEL::removeEdge(HalfEdge *&h)
{
    HalfEdge *t = h->twin;
    HalfEdge *h1_prev = h->prev;
    HalfEdge *h1_next = t->next;
    HalfEdge *h2_prev = t->prev;
    HalfEdge *h2_next = h->next;
    h1_prev->next = h1_next;
    h2_prev->next = h2_next;
    h1_next->prev = h1_prev;
    h2_next->prev = h2_prev;
    Face *f1 = h->f;
    Face *f2 = t->f;
    HalfEdge *temp = h1_next;
    temp->f = f1;
    temp = temp->next;
    while (temp != h1_next)
    {
        temp->f = f1;
        temp = temp->next;
    }
    f1->he = h1_next;
    free(h);
    vector<Face *> f;
    for (int i = 0; i < faces.size(); i++)
    {
        if (faces[i] != f2)
            f.push_back(faces[i]);
    }
    faces = f;
}

void DCEL::addVertex(double x, double y)
{
    Vertex *v = new Vertex();
    v->x = x;
    v->y = y;
    v->index = vertexID++;
    vertices.push_back(v);
}

void DCEL::addFace(int id)
{
    Face *f = new Face(id);
    faces.push_back(f);
}

void DCEL::createPolygon(char *file)
{
    if (edges.size() != 0)
    {
        cout << "Polygon already created!" << endl;
        return;
    }
    freopen(file, "r", stdin);
    int n;
    cin >> n;
    double x, y;
    while (n--)
    {
        cin >> x >> y;
        addVertex(x, y);
    }
    n = vertices.size();
    addFace(1);
    for (int i = 0; i < vertices.size(); i++)
    {
        HalfEdge *he = new HalfEdge();
        HalfEdge *t = new HalfEdge();
        he->v = vertices[i];
        he->f = faces[1];
        t->v = vertices[(i + 1) % n];
        t->f = faces[0];
        he->twin = t;
        t->twin = he;
        faces[1]->he = he;
        faces[0]->he = t;
        edges.push_back(new Edge(he, t));
    }
    for (int i = 0; i < edges.size(); i++)
    {
        edges[i]->edge.first->next = edges[(i + 1) % n]->edge.first;
        edges[i]->edge.first->prev = edges[(i - 1 + n) % n]->edge.first;
    }
    for (int i = 0; i < edges.size(); i++)
    {
        edges[i]->edge.second->next = edges[(i - 1 + n) % n]->edge.second;
        edges[i]->edge.second->prev = edges[(i + 1) % n]->edge.second;
    }
}

void DCEL::print_()
{
    for (int i = 0; i < faces.size(); i++)
    {
        HalfEdge *temp = faces[i]->he;
        cout << "Face: " << faces[i]->id << '\n';
        cout << temp->v->index << " ";
        temp = temp->next;
        while (temp != faces[i]->he)
        {
            cout << temp->v->index << " ";
            temp = temp->next;
        }
        cout << '\n';
    }
}
void DCEL::outputPolygon(char *file)
{
    FILE *fp = freopen(file, "w+", stdout);
    for (int i = 0; i < faces.size(); i++)
    {
        HalfEdge *temp = faces[i]->he;
        // cout << "Face: " << faces[i]->id << '\n';
        cout << temp->v->x << " " << temp->v->y << '\n';
        temp = temp->next;
        while (temp != faces[i]->he)
        {
            cout << temp->v->x << " " << temp->v->y << '\n';
            temp = temp->next;
        }
        cout << "$\n";
    }
    fclose(fp);
}
DCEL::~DCEL()
{
    vertices.clear();
    edges.clear();
    faces.clear();
}

// int main()
// {
//     DCEL *dcel = new DCEL();
//     char in[] = "input.txt";
//     dcel->createPolygon(in);
//     HalfEdge *h = dcel->addEdge(dcel->vertices[0], dcel->vertices[3], dcel->faces[1]);
//     dcel->print_();
//     dcel->removeEdge(h);
//     dcel->print_();
//     cout << '\n';
//     dcel->addEdge(dcel->vertices[0], dcel->vertices[8], dcel->faces[3]);
//     dcel->print_();
// }