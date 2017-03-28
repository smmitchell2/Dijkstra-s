#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "dll.h"
#include "vertex.h"
#include "string.h"
#include "binheap.h"
#include "array.h"
#include "helper.h"

int main(int argc,char **argv){
  char *file;
  if (!argv[1]) {exit(0);}
  else{file = argv[1];}
  int **m = initMatrix(file); vertex *root = newvertex(-1);
  m = fillMatrix(file,m);
  root = setRoot(m);
  binheap *b = fillTree(m,root); root = b->vertices[root->verName];
  while(b->size > 0){
    vertex *nextRoot = prims(m, b);
    breadthFirstSearch(m,b,root);
    root = nextRoot;
  }
  argc = 0;
  return argc;
}
