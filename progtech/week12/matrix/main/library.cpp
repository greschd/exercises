/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.2
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

typedef double* matrix_type;

#ifndef N
    #define N 1024
#endif
#ifndef ITER
    #define ITER 10
#endif

extern "C" {
    void dgemm_(char const & TRANSA, char const & TRANSB, int const & M,
    int const & SIZE, int const & K, double const & alpha, double * A, int const & LDA,
    double * B, int const & LDB, double const & beta, double* C, int const & LDC);
}

inline void multiply(matrix_type const & A, matrix_type const & B, matrix_type & C) {
    dgemm_('n', 'n', N, N, N, 1, B, N, A, N, 0, C, N); // switch A and B to account for Fortran matrix storing
}

#include "main.cpp"
