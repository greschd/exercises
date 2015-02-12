/*
* comp.c - contains the function superslow that you need to optimize
*
* How to write fast numerical code, spring 2014
* Alen Stojanov, Daniele Spampinato, Markus Pueschel
* ETH Zurich
*
*/

#include <math.h>
#include <stdio.h>
#include "comp.h"
#include "perf.h"

double f(double x, double y, double z, double * y1, double * y2, int i)
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

double fasterf(double x, double y, double z, double * y1, double * y2, int i)
{
	double t[3];

	if ( (i & 1) == 0 ) {
		t[0] = sin(x + y);
		t[1] = t[0] * 3;
		t[2] = sin(x - y) * 7;
	}
	else {
		t[0] = sin(x - y);
		t[1] = sin(x + y) * 3;
		t[2] = t[0] * 7;
	}

	double ytilde = y + 47;
	double s = sin(sqrt(ytilde + x * 0.5));
	*y1 = - t[0] * ytilde + t[1] * z * s - x * t[2] * sin(sqrt(-z + ytilde));
	*y2 = - t[2] * ytilde + t[0] * z * sin(sqrt( ytilde)) - x * t[0] * s;

	return *y1 + *y2;
}


/* This is the function you need to optimize. It takes one
square matrix as input
*/
void superslow(smat_t *a)
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
			// First, compute f(A) for the element of a in question
			x0 = get_elt(a,i-1,j);
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);
			y3  = f(x0, x1, x2, &y1, &y2, i);
			y3 += f(x0, x1, x2, &y2, &y1, i);
			// Add this to the value of a we're computing and store it
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i-1, j, y3);
			set_elt(a, i+0, j, sum1);
			set_elt(a, i+1, j, sum2);
		}
	}
}

void using_fasterf(smat_t *a)
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
			// First, compute f(A) for the element of a in question
			x0 = get_elt(a,i-1,j);
			x1 = get_elt(a,i,j);
			x2 = get_elt(a,i+1,j);
			y3 = fasterf(x0, x1, x2, &y2, &y1, i);
			y3 *= 2;
			// Add this to the value of a we're computing and store it
			sum1 = get_elt(a, i, j) + y1;
			sum2 = get_elt(a, i+1, j) + y2;
			set_elt(a, i-1, j, y3);
			set_elt(a, i+0, j, sum1);
			set_elt(a, i+1, j, sum2);
		}
	}
}

void fast(smat_t *a) {
	int i, j;
	double x0, x1, x2, x3, x4, x5;
	double y0, y1, y2, y3;
	double t0, t1, t2, t3, t4, t5;
	double * b = a->mat;
	int n = a->n;
	double ytilde, ytilde2;
	double s, s2;
	int inj, inj3;

	// i is the row of a we're computing right now
	for(i = 1; i < n; i += 6)
	{
		// j is the column of a we're computing right now
		for(j = 0; j < n; j++)
		{
			inj = i * n + j;
			inj3 = (i + 3) * n + j;
			// First, compute f(A) for the element of a in question
			x0 = b[inj - n];
			x1 = b[inj];
			x2 = b[inj + n];
			x3 = b[inj3 - n];
			x4 = b[inj3];
			x5 = b[inj3 + n];
			
			t0 = sin(x0 - x1);
			t1 = sin(x0 + x1) * 3;
			t2 = t0 * 7;
			t3 = sin(x3 + x4);
			t4 = t3 * 3;
			t5 = sin(x3 - x4) * 7;

			ytilde = x1 + 47;
			ytilde2 = x4 + 47;
			s = sin(sqrt(ytilde + x0 * 0.5));
			s2 = sin(sqrt(ytilde2 + x3 * 0.5));
			y1 = - t0 * ytilde + t1 * x2 * s - x0 * t2 * sin(sqrt(-x2 + ytilde));
			y0 = - t2 * ytilde + t0 * x2 * sin(sqrt(ytilde)) - x0 * t0 * s;
			y3 = - t3 * ytilde2 + t4 * x5 * s2 - x3 * t5 * sin(sqrt(-x5 + ytilde2));
			y2 = - t5 * ytilde2 + t3 * x5 * sin(sqrt(ytilde2)) - x3 * t3 * s2;
			// Add this to the value of a we're computing and store it
			b[inj - n] = 2 * (y0 + y1);
			b[inj] += y0;
			b[inj + n] += y1;
			b[inj3 - n] = 2 * (y2 + y3);
			b[inj3] += y2;
			b[inj3 + n] += y3;
		}
	}
}


/* 
* Called by the driver to register your functions
* Use add_function(func, description) to add your own functions
*/
void register_functions()
{
	// Registers comp_superslow with the driver
	add_function(&superslow, "superslow: original function");

	// Add your functions here
	add_function(&using_fasterf, "using_fasterf: strength reduction in f and removing unnecessary function call");
	add_function(&fast, "fast: avoiding the if, scalar replacement, inline function call");


}
