// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    03.10.2013 15:40:53 CEST
// File:    simpson.hpp

// Function:Simpson
// PRE:     Input:      A function pointer on a function taking a double and returning a double
//                      2 doubles a, b 
//                      An integer N > 0.
// POST:                Output is the integral over (a,b) of the function using the Simpson integration rule over N bins.
// Depends on:          libraries iostream, assert.h

#ifndef __SIMPSON_HEADER
#define __SIMPSON_HEADER

#include <assert.h>
#include <limits>
#include <stdexcept>


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

class func_class {
public:
    typedef double f_result_type;
    typedef double argument_type; 
    virtual f_result_type operator()(const argument_type) const = 0;
};

template <class T>
typename result_type<T>::type simpson(func_class const & func, T const & a, T const & b, const int & N) {
    if(N == 0) {
        throw std::range_error("zero steps not allowed");
    }
    // asserting valid function parameters 
    assert(N > 0);   
    
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
