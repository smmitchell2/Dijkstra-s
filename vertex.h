#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll.h"
#include "queue.h"
#include "integer.h"
#include "binomial.h"
#include "darray.h"

#ifndef __VERTEX_INCLUDED__
#define __VERTEX_INCLUDED__

typedef struct Edge{
	int from, to;
	int weight;
} Edge;


typedef struct Vertex{
	int value;
	int visited;
	int ID;
	int touched;
	struct Vertex *prev;
	DArray *adjacentV;
	BinomialNode *node;
} Vertex;

typedef struct Adjacent{
	Vertex *vertex;
	int weight;
} Adjacent; 


extern Edge *readData(FILE *);
extern Vertex *startVertex(DArray *);
extern void insertVertex(DArray *, int , int, int );
extern Adjacent *findAdjacency(DArray *, int );
extern Vertex *findVertex(DArray *, int );
extern void displayVertex(FILE *, void *);
extern int compareVertex(void *, void *);
extern void updateVertex(void *, BinomialNode *);
extern Binomial *fillHeap(DArray *);

#endif