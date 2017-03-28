//#include "node.h"

typedef struct binheap{
  int size;
  int (*comp)(void *,void *);
  dll *rootlist;
  void *min;
  vertex **vertices;
}binheap;

binheap *newBinHeap(int(*c)(void *, void *));
node *insertBinHeap(binheap *b,void *v);
vertex *addVerticesToRootlist(binheap *b, void *v, int infinity);
node *extractBinHeap(binheap *b);
void consolidate(binheap *b);
node *combine(binheap *b, node *x, node *y);
void updateConsolidationArray(binheap *b, node ** D,node *spot);
dll *setParent(dll *dll);
node *decreaseKeyBinHeap (binheap *b, node *n, void *nv);
node *bubbleUp(binheap *b, node *n);
vertex *updateValueKey(vertex *v, int weight, binheap *b, vertex *u);
