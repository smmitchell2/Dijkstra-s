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
	for(i = 1;i < sizeDArray(d);++i){
		Vertex *v = getDArray(d, i);
		if(v->value < minimum->value){
			minimum = v;
		}
	}
	return minimum;
}

void insertVertex(DArray *d, int vert, int connected, int weight){
	Vertex *v = findVertex(d, vert);

	if(v != NULL){
		Adjacent *a = findAdjacency(v->adjacentV, connected);
		if(a != NULL){
			if(a->weight > weight){
				a->weight = weight;
			}
		}
		else{
			a = newAdjacency(connected, weight);
			insertDArray(v->adjacentV, a);
		}
	}
	else{
		v = newVertex(vert);
		Adjacent *adj = newAdjacency(connected, weight);
		insertDArray(v->adjacentV, adj);
		insertDArray(d, v);
	}	
}

Vertex *findVertex(DArray *d, int vertex){
	int i;
	for(i = 0;i < sizeDArray(d);++i){
		Vertex *v = getDArray(d, i);
		if(v->value == vertex){
			return v;
		}
	}
	return NULL;
}

Adjacent *findAdjacency(DArray *d, int v){
	int i;
	for(i = 0;i < sizeDArray(d);++i){
		Adjacent *a = getDArray(d, i);
		if(a->vertex->value == v){
			return a;
		}
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
	int i;
	for(i = 0;i < sizeDArray(list);++i){
		Vertex *v = getDArray(list, i);
		v->node = insertBinomial(b, v);
	}	
	return b;
}