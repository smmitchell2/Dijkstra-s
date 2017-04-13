/*head component to comparator.c*/
#include <stdio.h>
#include "integer.h"
#include "real.h"
#include "string.h"

#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*, void*);

extern int intComparator(void *x, void *y);
extern int realComparator(void *x, void *y);
extern int stringComparator(void *x, void *y);

#endif