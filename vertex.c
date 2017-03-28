#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "dll.h"
#include "vertex.h"

vertex * newvertex(int i){
    vertex *o = malloc(sizeof(vertex) +1);
    o->verName = i;
    o->key = 0;
    o->owner = NULL;
    o->predecessor = -1;
    o->color = 'w';
    o->spot = 0;
    return o;
}

int vertexComparator(void *v,void *vv){
    vertex *a = (vertex*)v;
    vertex *b = (vertex*)vv;
    if(a->key - b->key == 0){
      if(a->predecessor - b->predecessor == 0){
        return a->verName - b->verName;
      }
      else return a->predecessor - b->predecessor;
    }
    else {return a->key - b->key;}
}

//From beastie
//Was having issues with similar keys so added name comparator in there to fix it
int vertexNameComparator(void *v,void *vv){
  vertex *a = (vertex*)v;
  vertex *b = (vertex*)vv;
  if(a->verName - b->verName == 0){
    if(a->predecessor - b->predecessor == 0){
      return a->key - b->key;
    }
    else return a->predecessor - b->predecessor;
  }
  else {return a->verName - b->verName;}
}
