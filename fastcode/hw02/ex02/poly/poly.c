#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "rdtsc.h"

#ifndef COST
#define COST (N*(N + 1)/2 + N + 1)
#endif
#ifndef FUNC
#define FUNC poly
#endif

typedef int size_type;

void poly(double * a, size_type N, double x, double * r) {

    int i,j;
    double t;
  
    *r = 0.;

    for(i = 0; i < N+1; i++) {

        t = a[i];

        for( j = 0; j < i; j++) {
            t *= x;
        }
    
        *r += t;
    
    }

}

void horner(double * a, size_type N, double x, double * r) {

    int i;
    *r = a[N];
    
    for (i = 0; i < N; i++) {
        
        *r *= x;
        *r += a[N - 1 - i];
        
    }
    
}

void horner2(double * a, size_type N, double x, double * r) {
    
    // polynom of order >= R - 1: use accumulators
    #define R 8
    if(N > R - 2) {
        int i;
        double r0, r1, r2, r3, r4, r5, r6, r7;
        r0 = a[N];
        r1 = a[N - 1];
        r2 = a[N - 2];
        r3 = a[N - 3];
        r4 = a[N - 4];
        r5 = a[N - 5];
        r6 = a[N - 6];
        r7 = a[N - 7];
        double xpow = x*x*x*x*x*x*x*x;
        for (i = 1; i < (N + 1) / R ; ++i)
        {
            r0 = r0 * xpow + a[N - R * i];
            r1 = r1 * xpow + a[N - R * i - 1];
            r2 = r2 * xpow + a[N - R * i - 2];
            r3 = r3 * xpow + a[N - R * i - 3];
            r4 = r4 * xpow + a[N - R * i - 4];
            r5 = r5 * xpow + a[N - R * i - 5];
            r6 = r6 * xpow + a[N - R * i - 6];
            r7 = r7 * xpow + a[N - R * i - 7];
        }
        
        *r = r0 * x*x*x*x*x*x*x + r1 * x*x*x*x*x*x + r2 * x*x*x*x*x + r3 * x*x*x*x + r4 * x*x*x + r5 * x*x + r6 * x + r7;
        
        double xtemp = 1;
        double rtemp = 0;
        for (i = 0; i < (N + 1) % R; ++i)
        {
            rtemp += a[i]*xtemp;
            xtemp *= x;
        }
        *r *= xtemp;
        *r += rtemp;
    }
    #undef R
    
    // low - N case: resort to horner 
    else {
        horner(a, N, x, r);
    }
  
}

void horner2_template (double * a, size_type N, double x, double * r) {
    
    // polynom of order >= R - 1: use accumulators
    #define R 8
    if(N > R - 2) {
        int i;
        double r0, r1, r2, r3, r4, r5, r6, r7;
        r0 = a[N];
        r1 = a[N - 1];
        r2 = a[N - 2];
        r3 = a[N - 3];
        r4 = a[N - 4];
        r5 = a[N - 5];
        r6 = a[N - 6];
        r7 = a[N - 7];
        double xpow = x*x*x*x*x*x*x*x;
        for (i = 1; i < (N + 1) / R ; ++i)
        {
            r0 = r0 * xpow + a[N - R * i];
            r1 = r1 * xpow + a[N - R * i - 1];
            r2 = r2 * xpow + a[N - R * i - 2];
            r3 = r3 * xpow + a[N - R * i - 3];
            r4 = r4 * xpow + a[N - R * i - 4];
            r5 = r5 * xpow + a[N - R * i - 5];
            r6 = r6 * xpow + a[N - R * i - 6];
            r7 = r7 * xpow + a[N - R * i - 7];
        }
        
        *r = r0 * x*x*x*x*x*x*x + r1 * x*x*x*x*x*x + r2 * x*x*x*x*x + r3 * x*x*x*x + r4 * x*x*x + r5 * x*x + r6 * x + r7;
        
        double xtemp = 1;
        double rtemp = 0;
        for (i = 0; i < (N + 1) % R; ++i)
        {
            rtemp += a[i]*xtemp;
            xtemp *= x;
        }
        *r *= xtemp;
        *r += rtemp;
    }
    #undef R
    
    // low - N case: resort to horner 
    else {
        horner(a, N, x, r);
    }
  
}

/*
 * Do not need to modify from here ...
 */

#define RUNS     2
#define CYCLES_REQUIRED 1e7
#define STRI(x) #x
#define STR(x) STRI(x)

void validate(double v, double * a, size_type N, double x)
{
    int i,j;
    double rerr, t, r = 0.;

    for(i = 0; i < N+1; i++) {

        t = a[i];

        for( j = 0; j < i; j++) {
            t *= x;
        }
        
        r += t;
        
    }
    
    rerr = fabs(r - v)/r;

#ifndef MEASURE
    printf("Ref:  p(%.1f) = %f\n", x, r);
    printf(STR(FUNC) ": p(%.1f) = %f\n", x, v);
    printf("Relative error: %.2f\n\n", rerr);
#endif
#ifdef MEASURE
    std::cout << rerr;
#endif

}

double test(double * a, size_type N, double x)
{
    tsc_counter start, end;
    double cycles = 0., r;
    size_type num_runs = RUNS, multiplier = 1;
    int i;


  //Cache warm-up + timing setup
    do{
        num_runs = num_runs * multiplier;
        CPUID(); RDTSC(start);
        for(i = 0; i < num_runs; i++) {
            FUNC(a, N, x, &r);
        }
        CPUID(); RDTSC(end);

        cycles = (double)(COUNTER_DIFF(end, start));
        multiplier = ceil (  (CYCLES_REQUIRED) / (cycles)  + 1.0 );

    }while (multiplier > 2);

    CPUID(); RDTSC(start);
    for (i = 0; i < num_runs; ++i) {
        FUNC(a, N, x, &r);
    }
    CPUID(); RDTSC(end);

    cycles = (double)(COUNTER_DIFF(end, start))/num_runs;

#ifndef MEASURE
    printf("Polynomial with N = %lu  - Performance [flops/cycle]: %.2f\n", N, COST/cycles);
    printf("Op count [flops]: %lu\n", COST);
    printf("Runtime [cycle]: %.2f\n", cycles);
#endif
#ifdef MEASURE
    std::cout << N << " " << COST/cycles << " " << COST << " " << cycles << " ";
#endif

    return r;
  
}

void setrandom(double * m, size_type M, size_type N)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < M*N; ++i)  m[i] = (double)(rand())/RAND_MAX;;
}

/*
 * ... to here.
 */


int main(int argc, char **argv)
{
    double v, *a;
    size_type N;
  
    N = atoi(argv[1]);
    a = (double *) malloc(sizeof(double)*(N+1));
  
    setrandom(a, N+1, 1);

    v = test(a, N, 0.2);
  
    validate(v, a, N, 0.2);
  
    return 0;
}
