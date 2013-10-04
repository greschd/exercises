// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    25.09.2013 13:20:35 CEST
// File:    simpson.cpp
// PRE:     Input is a non-zero natural number N giving the number of bins (0,Pi) will be split into
// POST:    Output is the integral over (0,Pi) of sin(x) using the Simpson integration rule over N bins.

#include <iostream>
#include <math.h>
#include <assert.h>
#include "simpson.hpp"

double simpson(double (*func)(double), double a, double b, int N){

    // asserting valid function parameters 
    assert(N > 0);   // I didn't want to use unsigned int because a small negative input would produce huge N
    assert(b > a);

    // Computing the step between two bins
    const double step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    double sum(0);
    const double a_new = a + step / 2;
    for(int i = 0; i < N ; ++i){
        sum += (*func)(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(int j = 1; j < N; ++j){
        sum += (*func)(a + j * step);
        }
    
    // Adding the boundaries & factor, return
    return (sum + ((*func)(a) + (*func)(b)) / 2) * step / 3;
    
}

