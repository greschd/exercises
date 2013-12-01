// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    03.10.2013 15:40:53 CEST
// File:    simpson.hpp


#ifndef __SIMPSON_HEADER
#define __SIMPSON_HEADER

#include <assert.h>

typedef double return_type;
typedef double result_type;
typedef double argument_type;
typedef unsigned int bin_type;

template <class FuncType>
double simpson_functionobject(FuncType func, const double & a, const double & b, const bin_type & N) {
    // Computing the step between two bins
    const argument_type step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    result_type sum(0);
    const argument_type a_new = a + step / 2;
    for(int i = 0; i < N ; ++i){
        sum += func(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(bin_type j = 1; j < N; ++j){
        sum += func(a + j * step);
        }
    
    // Adding the boundaries & factor, return
    return (sum + (func(a) + func(b)) / 2) * step / 3;
    
}

#endif //__SIMPSON_HEADER
