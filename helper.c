#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "string.h"
#include "vertex.h"
#include "array.h"
#include "dll.h"
#include "binheap.h"
#include "helper.h"

int size = 0;
int INF = 0;
int VertexCount = 0;

void *setVERtoVOID(vertex *a){
    node *b = malloc(sizeof(node));
    b->data = a;
    return b;
}

vertex *setRoot(int ** m){
  int i = 0;
  int j = 0;
  vertex *root = newvertex(size+1);
  for (i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      if (m[i][j] != INF){
        if(j < i && j < root->verName) {root->verName = j;}
        else if(i < j && i < root->verName) {root->verName = i;}
      }
    }
  }
  return root;
}

int ** initMatrix (const char *file){
  int i = 0, j = 0, ** m,count = 0;
  FILE *fp = fopen(file, "r");
  while (!feof(fp)){
    const char *a = readToken(fp);
    if(a != NULL && strcmp(a,";") != 0){
      if(count < 2 && atoi(a) > size) {size = atoi(a);}
      count++;
      if(atoi(a) > INF) {INF = atoi(a) + 1;}
    }
    else {count = 0;}
  }
  fclose(fp);
  size = size+1;
  m = malloc(sizeof(int *) * size);
  int *tmp =malloc(size *size * sizeof(int));
  i = 0;
  while( i < size){
    m[i] = &tmp[i*size];
     i++;
  }
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      m[i][j] = INF;
    }
  }
  return m;
}

int **fillMatrix(const char *file, int **m){
  int x = 0,count = 0,weight = 0, i = 0, j = 0;
  FILE *fp = fopen(file, "r");
  while (!feof(fp)){
    const char *a = readToken(fp);
    if(a != NULL){
        if(*a ==';'){
          if(m[i][j] == INF){
            if(weight == 1) {m[i][j] = x; m[j][i] = x;}
            else{
              m[i][j] = 1;
              m[j][i] = 1;
            }
          }
          count = 0; weight = 0;
        }
        else{
          x = atoi(a);
          if (count == 0) {j = x;}
          else if (count == 1) {i = x;}
          else if (count == 2) {
            count = 0;
            weight = 1;
          }
          count++;
        }
      }
    }
  fclose(fp);
  return m;
}

vertex *prims(int **m, binheap *b){
  int i = 0,spot = 1; vertex *nextRoot = newvertex(-1);
  while(b->size != 0){
    node *n = extractBinHeap(b);
    vertex *u = (vertex*)n->data;
    if(u->key == INF){
      if(spot == 1){
        b->vertices[u->verName] = addVerticesToRootlist(b,u,0);
        nextRoot = b->vertices[u->verName]; spot = 0;
      }
      else {b->vertices[u->verName] = addVerticesToRootlist(b,u,INF);}
      break;
    }
    i = 0;
    while(i < size){
      if(m[u->verName][i] != INF){
        if(m[u->verName][i] < b->vertices[i]->key && b->vertices[i]->spot != 1){
          b->vertices[i] = updateValueKey(b->vertices[i],m[u->verName][i],b,b->vertices[u->verName]);
          b->vertices[u->verName]->spot = 1;
        }
      }
     i++;
    }
  }
  return nextRoot;
}

binheap *fillTree(int **m, vertex *root){
  int i = 0, j = 0, k = 0; vertex *v;
  binheap *b = newBinHeap(vertexComparator);
  b->vertices = malloc(sizeof(vertex) * size + 1);
  k = 0;
  while (k < size){
    b->vertices[k] = NULL;
    k++;
  }
  for(j = 0; j < size; j++){
    for(i = 0; i < size; i++){
      if(m[i][j] != INF){
        if(b->vertices[j] == NULL){
          v = newvertex(j); VertexCount++;
          if(root->verName == j){b->vertices[j] = addVerticesToRootlist(b,v,0);}
          else{b->vertices[j] = addVerticesToRootlist(b,v,INF);}
        }
        if(b->vertices[i] == NULL){
          v = newvertex(i); VertexCount++;
          if(root->verName == i){b->vertices[i] = addVerticesToRootlist(b,v,0);}
          else{b->vertices[i] = addVerticesToRootlist(b,v,INF);}
        }
      }
    }
  }
  return b;
}

void printBFSArray(array *vertexArray){
  int i = 0;
  while(i < vertexArray->size){
    vertex *v1 = vertexArray->store[i];
    printf("%d(%d)%d",v1->verName,v1->predecessor,v1->key);
    if(i < vertexArray->size-1) {printf(", ");}
    else if (i == vertexArray->size-1) {printf(";");}
    ++i;
    }
}

void breadthFirstSearch(int **m, binheap *b, vertex *root){
  int i, totalWeight = 0, distance = 0, a = 0; dll *d = newDLL();
  vertex *temp = NULL, *v1 = NULL;
  array printEdgeArray = *newArray(vertexNameComparator);
  i = 0;
  while(i < size){
    temp = b->vertices[i];
    if(temp != NULL){
      temp->color = 'w';
      temp->distance = distance;
    }
    ++i;
  }
  root = b->vertices[root->verName];
  root->color = 'g';
  root->predecessor = 0;
  printf("%d : %d;",root->distance,root->verName);
  insertInPriQu(d,setVERtoVOID(NULL)); insertInPriQu(d,setVERtoVOID(root));
  while(d->size != 1){
    node *n = Delete(d); temp = n->data;
    if(temp == NULL){
      if(a!= 0) {printf("\n%d : ",a);}
      a++;
      sortArray(&printEdgeArray); printBFSArray(&printEdgeArray);
      printEdgeArray = *newArray(vertexNameComparator);
      insertInPriQu(d,setVERtoVOID(NULL));continue;
    }
    i = 0;
    while(i < size){
      if(m[temp->verName][i] != INF && b->vertices[i]->predecessor == temp->verName){
        v1 = b->vertices[i];
        if(v1->color == 'w'){
          v1->color = 'g';
          totalWeight += v1->key;
          addArray(&printEdgeArray, v1);
          if(v1->predecessor != -1){insertInPriQu(d,setVERtoVOID(v1));}
        }
      }
      ++i;
    }
    if(temp->verName != root->verName){b->vertices[v1->predecessor]->color = 'b';}
  }
  printf("\nweight: %d\n", totalWeight);
}
