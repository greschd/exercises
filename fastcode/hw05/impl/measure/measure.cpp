// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    01.04.2014 18:33:20 CEST
// File:    measure.cpp

#include "rdtsc.h"

#ifdef V0
#include "../src/code0.c"
#endif

#ifdef V1
#include "../src/code1.c"
#endif

#ifdef V2
#include "../src/code2.c"
#endif

#ifdef V3
#include "../src/code3.c"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <random>
#include <ctime>

#ifndef NUM_RUNS
#define NUM_RUNS 100
#endif
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 2.4e9

#define CALIBRATE



/* 
 * Timing function based on the TimeStep Counter of the CPU.
 */

double rdtsc() {
    int i, num_runs;
    double cycles;
    tsc_counter start, end;
  
    num_runs = NUM_RUNS;

/* 48
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
    
    double r;
    
    A = (double*)malloc(NB*NB*sizeof(double));
    B = (double*)malloc(NB*NB*sizeof(double));
    C = (double*)malloc(NB*NB*sizeof(double));

    std::mt19937 rng(std::time(NULL));
    std::uniform_real_distribution<double> distr;
    
    for(uint i = 0; i < NB; ++i) {
        for(uint j = 0; j < NB; ++j) {
            A[i * NB + j] = distr(rng);
            B[i * NB + j] = distr(rng);                             
            C[i * NB + j] = distr(rng);                             
        }                                                           
    }   

    r = rdtsc();
    std::cout << r << std::endl;
    
    return 0;
}

