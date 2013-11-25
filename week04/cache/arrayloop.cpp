// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    12.10.2013 11:55:18 CEST
// File:    arrayloop.cpp
// PRE:     Input are the three unsigned integers N, step, n
// POST:    The function creates an array of size N increments every step-th element until n elements have been incremented 

#include <iostream>
#include <assert.h>
#include "arrayloop.hpp"

void arrayloop(uint const & N, uint const & step, uint const & n) {
    assert(N > 0);
    assert(step > 0);
    assert(n > 0);
    
    // Creating the array
    double *a = new double[N];
    
    // looping over the array, incrementing every "step"th element
    for(uint i = 0; i < n; ++i) {
        ++a[(i * step) % N];
    }
    
    //Deleting the array
    delete[] a;
}

