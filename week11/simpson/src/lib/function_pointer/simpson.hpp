// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    03.10.2013 15:40:53 CEST
// File:    simpson.hpp

// Function:Simpson
// PRE:     Input:      A function pointer on a function taking a double and returning a double
//                      2 doubles a, b 
//                      An integer N > 0.
// POST:    Output is the integral over (a,b) of the function using the Simpson integration rule over N bins.
// Depends on:          libraries iostream, math.h, assert.h

#ifndef __SIMPSON_HEADER
#define __SIMPSON_HEADER

#include <iostream>
#include <math.h>
#include <assert.h>

typedef double result_type;
typedef double argument_type;
typedef unsigned int bin_type;

result_type simpson_functionpointer(result_type (*func)(const argument_type &),const argument_type & a,const argument_type & b,const bin_type & N){

    // Computing the step between two bins
    const double step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    double sum(0);
    const double a_new = a + step / 2;
    for(bin_type i = 0; i < N ; ++i){
        sum += (*func)(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(bin_type j = 1; j < N; ++j){
        sum += (*func)(a + j * step);
        }
    
    // Adding the boundaries & factor, return
    return (sum + ((*func)(a) + (*func)(b)) / 2) * step / 3;
    
}

#endif //__SIMPSON_HEADER
