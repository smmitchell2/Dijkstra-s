#include <stdio.h>
#include <stdlib.h>
#include "darray.h"
#include "integer.h"

struct DArray{
	void **array; 
	int capacity; 
	int size; 	  
	void (*display)(FILE *, void *); 
};

DArray *newDArray(void (*display)(FILE *,void *)){
	DArray *a = malloc(sizeof(DArray)); 
	a->array = malloc(sizeof(void *)*1);
	a->capacity = 1;
	a->size = 0;
	a->display = display;

	return a;
}

void insertDArray(DArray *a,void *v){
	if(a->size == a->capacity) 
	{
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	a->array[a->size++] = v;
}

void *removeDArray(DArray *a){
	void *rv = a->array[a->size-1];
	if(a->size == 0){
		fprintf(stderr, "Attempting to remove from an empty array\n");
		exit(-1);
	}

	a->array[a->size-1] = NULL;
	--a->size;
	double size = a->size;
	double capacity = a->capacity;

	
	if(size < capacity/4.0 && capacity > 2){
		a->capacity /= 2; 
		a->array = realloc(a->array, a->capacity * sizeof(void *));
	}
	return rv;
}

void *getDArray(DArray *a,int index){
	return a->array[index];
}

void setDArray(DArray *a,int index,void *value){
	if(index == a->size) {
		return insertDArray(a, value);
	}

	a->array[index] = value;
}

int sizeDArray(DArray *a){
	return a->size;
}

void displayDArray(FILE *fp,DArray *a){

	int index = 0;
	fprintf(fp,"[");
	while(a->size - index > 0){
		a->display(fp,a->array[index]);
		if(index + 1 < a->size) {
			fprintf(fp, ",");
		}

		index++;
	}
	fprintf(fp, "]");

	fprintf(fp, "[%d]", a->capacity - a->size);
}
