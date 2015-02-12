/*
 * verfunc.c - contains the function superslow that you need to optimize
 *
 * How to write fast numerical code, spring 2014
 * Alen Stojanov, Daniele Spampinato, Markus Pueschel
 * ETH Zurich
 */

#include <math.h>
#include "comp.h"
#include "perf.h"

double ver_f(double x, double y, double z, double * y1, double * y2, int i)
{
	double t[3];

	if ( round(i/2.0) == (float)(i >> 1) )
		t[0] = sin(x) * cos(y) + cos(x) * sin(y);
	else
		t[0] = sin(x) * cos(y) - cos(x) * sin(y);
	t[1] = sin(x + y) * 3;
	t[2] = sin(x - y) * 7;

	*y1 = - t[0] * (y + 47) + t[1] * z * sin(sqrt(fabs(y + (x/2.0) + 47))) - x * t[2] * sin(sqrt(fabs(z - y - 47)));
	*y2 = - t[2] * (y + 47) + t[0] * z * sin(sqrt(fabs(- y - 47))) - x * t[0] * sin (sqrt(fabs(y + 47 + x * 0.5)));

	return *y1 + *y2;
}


/* This is the function you need to optimize. It takes one
square matrix as input
 */
void verfunc(smat_t *a)
{
	int i, j;
	double x0, x1, x2, y1, y2, y3;
	double sum1, sum2;

	// j is the column of a we're computing right now
	for(j = 0; j < a->n; j++)
	{
		// i is the row of a we're computing right now
		for(i = 1; i < a->n; i += 3)
		{
			x0 = get_elt(a,i-1,j);
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);
			y3  = ver_f(x0, x1, x2, &y1, &y2, i);
			y3 += ver_f(x0, x1, x2, &y2, &y1, i);
			// Add this to the value of a we're computing and store it
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i-1, j, y3);
			set_elt(a, i+0, j, sum1);
			set_elt(a, i+1, j, sum2);
		}
	}
}
