

void *setVERtoVOID(vertex *a);
vertex *setRoot(int **m);
int **initMatrix (const char *file);
int **fillMatrix(const char *file, int **m);
vertex *prims(int **m, binheap *b);
binheap *fillTree(int **m, vertex *root);
void printBFSArray(array *vertexArray);
void breadthFirstSearch(int **m, binheap *b, vertex *root);
