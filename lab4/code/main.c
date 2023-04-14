extern int proc(short *m, short *n, int u);

#include <stdio.h>
#include "data.h"

#define COUNT  256

short a[COUNT] = {A_ARRAY};
short x[COUNT] = {X_ARRAY};
int y = 0;

/* Main Code */
main()
{
	int k = 0;
	y = proc(a, x, COUNT);
	printf("y = %x hex (%d decimal)\n", y, y);
	k++;
}