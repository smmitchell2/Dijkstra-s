#include <stdlib.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "comparator.h"

int intComparator(void *v,void *w){
  return ((integer *) v)->value - ((integer *) w)->value;
}

int stringComparator(void *a, void *b){
  return strcmp((char*)a,(char*)b);
}

int realComparator(void *v, void *w){
  double a = *(double*)v;
	double b = *(double*)w;
	if(a < b){return -1;}
	else if(a > b){return 1;}
	else{return 0;}
}