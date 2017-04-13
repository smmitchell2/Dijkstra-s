#include "vertex.h"
#include "scanner.h"
#include <limits.h>

Adjacent *newAdjacency(int , int );
Vertex *newVertex(int );
Vertex *startVertex(DArray *);//locates the minimum value as the start vertex
void insertVertex(DArray *, int , int , int);//insert vertex into adj list

Vertex *newVertex(int value){
	Vertex *newV = malloc(sizeof(Vertex));
	newV->value = value;
	newV->visited = 0;
	newV->ID = INT_MAX;
	newV->touched = 0;
	newV->prev = NULL;
	newV->adjacentV = newDArray(displayInteger);
	newV->node = NULL;
	
	return newV;
}

Adjacent *newAdjacency(int vertex, int weight){
	Adjacent *a = malloc(sizeof(Adjacent));
	a->vertex = newVertex(vertex);
	a->weight = weight;
	return a;
}

Edge *readData(FILE *fp){	
	char c = readChar(fp);
	if (c == EOF){
		return NULL;
	}
	ungetc(c, fp);
	Edge *e = malloc(sizeof(Edge));
	e->from = readInt(fp);
	e->to = readInt(fp);
	char *tok = readToken(fp);
	if(strcmp(tok, ";")){
		//if next value is not a ';' convert the token value to an integer
		e->weight = atoi(tok);	
		free(tok);
		tok = readToken(fp);
	}
	else{
		e->weight = 1;
		free(tok);
	}	
	return e;
}

Vertex *startVertex(DArray *d){
	if(sizeDArray(d) == 0){
		return NULL;
	}

	Vertex *minimum = (Vertex *) getDArray(d, 0);
	int i = 1;
	while(i < sizeDArray(d)){
		Vertex *v = getDArray(d, i);
		if(v->value < minimum->value){
			minimum = v;
		}
		++i;
	}
	return minimum;
}

void insertVertex(DArray *d, int vert, int friend, int weight){
	Vertex *v = findVertex(d, vert);

	if(v != NULL){
		Adjacent *a = findAdjacency(v->adjacentV, friend);
		if(a != NULL){
			if(a->weight > weight){
				a->weight = weight;
			}
		}
		else{
			a = newAdjacency(friend, weight);
			insertDArray(v->adjacentV, a);
		}
	}
	else{
		v = newVertex(vert);
		Adjacent *adj = newAdjacency(friend, weight);
		insertDArray(v->adjacentV, adj);
		insertDArray(d, v);
	}	
}

Vertex *findVertex(DArray *d, int vertex){
	int i=0;
	while(i < sizeDArray(d)){
		Vertex *v = getDArray(d, i);
		if(v->value == vertex){
			return v;
		}
		++i;
	}
	return NULL;
}

Adjacent *findAdjacency(DArray *d, int v){
	int i=0;
	while(i < sizeDArray(d)){
		Adjacent *a = getDArray(d, i);
		if(a->vertex->value == v){
			return a;
		}
		++i;
	}
	return NULL;
}

int compareVertex(void *x, void *y){								
	if(x == NULL && y == NULL){
		return 0;
	}
	else if(x == NULL){
		return -1;
	}
	else if(y == NULL){
		return 1;
	}

	Vertex *a = (Vertex *) x;
	Vertex *b = (Vertex *) y;

	if(a->ID == b->ID){
		if(a->value < b->value){
			return -1;
		}
		else{
			return 1;
		}
	}
	else if(a->ID < b->ID){
		return -1;
	}
	else{
		return 1;	
	}

}

void displayVertex(FILE *fp, void *value){
	Vertex *v = (Vertex *) value;
	fprintf(fp, "%d", v->value);
	if(v->prev != v && v->prev != NULL){
		fprintf(fp, "(%d)", v->prev->value);
		fprintf(fp, "%d", v->ID);
	}
}

void updateVertex(void *value, BinomialNode *n){
	Vertex *v = (Vertex *) value;
	v->node = n;
}

Binomial *fillHeap(DArray *list){
	Binomial *b = newBinomial(displayVertex, compareVertex, updateVertex);
	int i = 0;
	while(i < sizeDArray(list)){
		Vertex *v = getDArray(list, i);
		v->node = insertBinomial(b, v);
		++i;
	}	
	return b;
}