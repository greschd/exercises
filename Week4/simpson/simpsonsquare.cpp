// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    25.09.2013 13:20:35 CEST
// File:    simpson.cpp
// PRE:     Input:      A function pointer on a function taking a double and returning a double
//                      2 doubles a, b
//                      An integer N > 0.
// POST:    Output is the integral over (a,b) of the function using the Simpson integration rule over N bins.

#include <iostream>
#include <math.h>
#include <assert.h>
#include "simpsonsquare.hpp"

double simpsonsquare(const double & a,const double & b,const int & N){

    // asserting valid function parameters 
    assert(N > 0);   // I didn't want to use unsigned int because a small negative input would produce huge N
    
    // Handle the case a == b
    if(a == b)                                                                                                  // 1 flop
        return 0;
    
    // Computing the step between two bins
    const double step = (b - a) / N;                                                                            // 2 flops
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    double sum(0);
    const double a_new = a + step / 2;                                                                          // 2 flops
    for(int i = 0; i < N ; ++i){
        sum += pow(a_new + i * step, 2);                                                                        // 3 * N flops 
        }
    sum *= 2;                                                                                                   // 1 flop
    
    // Adding the rest, except the boundaries
    for(int j = 1; j < N; ++j){
        sum += pow(a + j * step, 2);                                                                            // 3 * N flops
        }
    
    // Adding the boundaries & factor, return
    return (sum + (pow(a, 2) + pow(b, 2)) / 2) * step / 3;                                                      // 7 flops
    
}

// The total number of double operations (flops) for N bins is 13 + 6 * N flops. 
