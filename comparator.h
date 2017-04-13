#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);

extern int intComparator(void *a,void *b);
extern int stringComparator(void *a, void *b);
extern int realComparator(void *a, void *b);

#endif