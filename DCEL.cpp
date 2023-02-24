#include <iostream>
#include <vector>
using namespace std;
class Face;
class Vertex
{
public:
    int index;
    double x;
    double y;
};
class HalfEdge
{
public:
    Vertex *v;
    Face *f;
    HalfEdge *twin;
    HalfEdge *next;
    HalfEdge *prev;
};
class Face
{
public:
    HalfEdge *he;
    int id;
    Face(int n) { id = n; }
};
class Edge
{
public:
    pair<HalfEdge *, HalfEdge *> edge;
    Edge(HalfEdge *a, HalfEdge *b)
    {
        edge.first = a;
        edge.second = b;
    }
};
class DCEL
{
public:
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    vector<Face *> faces;
    int faceID = 2;
    int vertexID = 0;
    DCEL()
    {
        faces.push_back(new Face(0));
    };
    void addEdge(Vertex *&v1, Vertex *&v2, Face *&currFace)
    {
        int fid = currFace->id;
        HalfEdge *fromV1 = new HalfEdge();
        HalfEdge *fromV2 = new HalfEdge();
        HalfEdge *halfV1, *halfV2;
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i]->edge.first->f->id == fid && edges[i]->edge.first->v == v1)
            {
                halfV1 = *&edges[i]->edge.first;
            }
            if (edges[i]->edge.second->f->id == fid && edges[i]->edge.second->v == v1)
            {
                halfV1 = *&edges[i]->edge.second;
            }
        }
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i]->edge.first->f->id == fid && edges[i]->edge.first->v == v2)
            {
                halfV2 = *&edges[i]->edge.first;
            }
            if (edges[i]->edge.second->f->id == fid && edges[i]->edge.second->v == v2)
            {
                halfV2 = *&edges[i]->edge.second;
            }
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
        // TODO: implement joining  logic
    }
    void removeEdge()
    {
        // TODO
    }
    void addVertex(double x, double y)
    {
        Vertex *v = new Vertex();
        v->x = x;
        v->y = y;
        v->index = vertexID++;
        vertices.push_back(v);
    }
    void addFace(int id)
    {
        Face *f = new Face(id);
        faces.push_back(f);
    }
    void createPolygon(char *file)
    {
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
    void print_()
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
    ~DCEL()
    {
        vertices.clear();
        edges.clear();
        faces.clear();
    }
};

int main()
{
    DCEL *dcel = new DCEL();
    char in[] = "input.txt";
    dcel->createPolygon(in);
    dcel->addEdge(dcel->vertices[0], dcel->vertices[7], dcel->faces[1]);
    dcel->print_();
    cout << '\n';
    dcel->addEdge(dcel->vertices[0], dcel->vertices[9], dcel->faces[1]);
    dcel->print_();
    cout << '\n';
    dcel->addEdge(dcel->vertices[0], dcel->vertices[8], dcel->faces[3]);
    dcel->print_();
}