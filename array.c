#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "array.h"

struct DArray{
    int size;
    int capacity;
    void(*dsp)(FILE *,void *);

}

static void Fatal(char *,...);
static void mergeSort(void **,int,int,void **,int (*)(void *,void *));

DArray *newDArray(int (*dsp)(void *,void *)){
    DArray *a = malloc(sizeof(DArray));
    if (a == 0) Fatal("out of memory\n");
    a->dsp =dsp;
    a->size = 0;
    a->capacity = 1;
    a->store = malloc(sizeof(void *) * a->capacity);
    if (a->store == 0) Fatal("out of memory\n");
    return a;
}

void insertDArray(DArray *a,void *v){
    if (a->size == a->capacity)
    {
        a->capacity *= 2;
        a->store = realloc(a->store,sizeof(void *)*a->capacity);
        if (a == 0) Fatal("out of memory\n");
    }
    a->store[a->size] = v;
    a->size += 1;
}

void *removeDArray(DArray *a){
    if(a->size == 1){}
}

void *getDArray(DArray *a,int index){

}

void setDArray(DArray *a,int index,void *value){

}

int sizeDArray(DArray *a){

}

void displayDArray(FILE *fp. DArray *a){

}

static void
Fatal(char *fmt, ...)
{
    va_list ap;
    
    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    
    exit(-1);
}