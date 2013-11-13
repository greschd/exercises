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

#include <assert.h>
#include <limits>

template <class T, bool F>
struct helper {
    typedef T type;
};

template <class T> 
struct helper<T, true> {
    typedef double type;
};

template <class T>
struct result_type {
    typedef typename helper<T, std::numeric_limits<T>::is_integer>::type type;
};

template <class FuncType, class T>
typename result_type<T>::type simpson(FuncType func, T const & a, T const & b, const int & N) {
    // asserting valid function parameters 
    assert(N > 0);   // I didn't want to use unsigned int because a small negative input would produce huge N
    
    // Handle the case a == b
    if(a == b)
        return 0;
    
    // Computing the step between two bins
    const typename result_type<T>::type step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    T sum(0);
    const typename result_type<T>::type a_new = a + step / 2;
    for(int i = 0; i < N ; ++i){
        sum += func(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(int j = 1; j < N; ++j){
        sum += func(a + j * step);
        }
    
    // Adding the boundaries & factor, return
    return (sum + (func(a) + func(b)) / 2) * step / 3;
    
}

#endif //__SIMPSON_HEADER
