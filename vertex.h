

typedef struct vertex{
    int distance;
    int verName;
    int key;
    int spot;
    void *owner;
    int predecessor;
    char color;
}vertex;

vertex * newvertex(int v);

int vertexComparator(void *v,void *vv);
int vertexNameComparator (void *v,void *vv);
