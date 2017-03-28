#include <stdio.h>
#include <stdlib.h>
//#include "node.h"
#include "dll.h"
#include "vertex.h"
#include "binheap.h"
#include "math.h"


binheap *newBinHeap(int(*comp)(void *, void *)){
  binheap *b = malloc(sizeof(binheap)+1);
  b->comp = comp;
  b->rootlist = newDLL();
  b->min = NULL;
  b->size = 0;
  b->vertices = NULL;
  return b;
}

node *decreaseKeyBinHeap(binheap *b, node *n, void *data){
  vertex *v = (vertex*)data;
  node *a = b->min;
  n->data = v;
  n = bubbleUp(b,n);
  if(b->comp(a->data,v) > 0) {b->min = n;}
  return n;
}

node *extractBinHeap(binheap *b){
  node *y = b->min;
  DeleteNode(b->rootlist,y);
  setParent(y->children);
  merge(b->rootlist,y->children);
  if(b->size > 1) {consolidate(b);}
  b->size--;
  return y;
}

node *bubbleUp(binheap *b, node *n){
  if(n == n->parent){return n;}
  else if(b->comp(n->data, n->parent->data) > 0) {return n;}
  else{
    vertex *a = n->data;
    a->owner = n->parent;
    a = n->parent->data;
    a->owner = n;
    vertex *temp = n->data;
    n->data = n->parent->data;
    n->parent->data = temp;
    return bubbleUp(b,n->parent);
  }
}

node *insertBinHeap(binheap *b,void *data){
  node *n = (node *)malloc(sizeof(node) +2);
  n->data = data;
  n->parent = n;
  n->children = newDLL();
  insert(b->rootlist,n);
  b->size++;
  consolidate(b);
  return n;
}

void consolidate(binheap *b){
  int i = 0;
  node **D;
  int Dsize = log2(b->size)+1;
  D = malloc(sizeof(node *) * (Dsize + 2));
  for(i = 0; i < Dsize; ++i) {D[i] = NULL;}
  while (b->rootlist->size != 0){
    node *spot = b->rootlist->head;
    DeleteNode(b->rootlist,spot);
    updateConsolidationArray(b,D,spot);
  }
  b->min = NULL;
  for (i = 0; i < Dsize; ++i){
      if (D[i] != NULL){
        insert(b->rootlist,D[i]); node *temp = b->min;
        if(b->min == NULL || b->comp(D[i]->data,temp->data) < 0){
            b->min = D[i];
        }
      }
  }
}

void updateConsolidationArray(binheap *b, node ** D,node *spot){
  int degree = spot->children->size;
  while (D[degree] != NULL){
    spot = combine(b,spot,D[degree]);
    D[degree] = NULL;
    degree++;
  }
  D[degree] = spot;
}

node *combine(binheap *b, node *x, node *y){
  if (b->comp(x->data,y->data) < 0){
    insert(x->children,y);
    y->parent = x;
    return x;
  }
  else{
    insert(y->children,x);
    x->parent = y;
    return y;
  }
}

dll *setParent(dll *dll){
  node *temp = dll->head;
  while (temp != NULL && temp->data != NULL){
    temp->parent = temp;
    temp = temp->next;
  }
  return dll;
}

vertex *addVerticesToRootlist(binheap *b, void *a, int inf){
  vertex *v = (vertex*)a;
  v->key = inf;
  v->owner = insertBinHeap(b,v);
  return v;
}

vertex *updateValueKey(vertex *v, int weight, binheap *b, vertex *u){
  if(u->predecessor != v->verName){
    v->predecessor = u->verName;
    v->key = weight;
  }
  if(v->spot != 1) {decreaseKeyBinHeap(b,v->owner, v);}
  return v;
}
