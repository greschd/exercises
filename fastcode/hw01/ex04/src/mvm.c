//#error Please comment out the next two lines under linux, then comment this error
//#include "stdafx.h" //Visual studio expects this line to be the first one, comment out if different compiler
//#include <windows.h> // Include if under windows

#ifndef WIN32
#include <sys/time.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#include "rdtsc.h"

//~ #define NUM_RUNS 1
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 3.06e9

#define CALIBRATE

int m, n;
double *A, *x, *y;

/* 
 * Straightforward implementation of matrix-matrix multiplication:
 * C = AB + C
 */

void compute() {
    int i,j;
    for(i = 0; i < m; ++i) {
        for(j = 0; j < n; ++j) {
            y[i] += A[i*n + j] * x[j];
        }
    }
}

/* 
 * Timing function based on the TimeStep Counter of the CPU.
 */

double rdtsc() {
    int i, num_runs;
    double cycles;
    tsc_counter start, end;
  
    num_runs = NUM_RUNS;

/* 
 * The CPUID instruction serializes the pipeline.
 * Using it, we can create execution barriers around the code we want to time.
 * The calibrate section is used to make the computation large enough so as to 
 * avoid measurements bias due to the timing overhead.
 */
#ifdef CALIBRATE
    while(num_runs < (1 << 14)) {
        CPUID(); RDTSC(start);
        for (i = 0; i < num_runs; ++i) {
            compute();
        }
        RDTSC(end); CPUID();

        cycles = (double)(COUNTER_DIFF(end, start));

        if(cycles >= CYCLES_REQUIRED) break;

        num_runs *= 2;
    }
#endif

    CPUID(); RDTSC(start);
    for (i = 0; i < num_runs; ++i) {
        compute();
    }
    RDTSC(end); CPUID();

    cycles = (double)(COUNTER_DIFF(end, start))/num_runs;
    return cycles;
}

int main(int argc, char **argv){

    int i;
    double r;
    if (argc!=3) {printf("usage: mmm <m> <n>\n"); return -1;}
    m = atoi(argv[1]);
    n = atoi(argv[2]);

    x = (double*)malloc(m*sizeof(double));
    A = (double*)malloc(m*n*sizeof(double));
    y = (double*)malloc(n*sizeof(double));

    for(i =0; i<m*n;i++) A[i]=i;
    for(i =0; i<n;i++) x[i]=i;

    r = rdtsc();
    
    std::cout << r;

    return 0;
}
