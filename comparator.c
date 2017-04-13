#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include <string.h>
#include "comparator.h"

int intComparator(void *x, void *y)
{
	int result = 0;

	int a = *((int *)x);
	int b = *((int *)y);

	if(a > b)
		result = 1;
	else if (a == b)
		result = 0;
	else
		result = -1;

	return result;
}
int realComparator(void *x, void *y)
{
	int result = 0;

	double a = *((double *)x);
	double b = *((double *)y);

	if(a > b)
		result = 1;
	else if (a == b)
		result = 0;
	else
		result = -1;

	return result;
}
int stringComparator(void *x, void *y)
{
	char *a = ((string *)x)->value;
	char *b = ((string *)y)->value;

	int result = strcmp(a, b);
	return result;
}