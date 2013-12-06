// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    06.12.2013 03:06:23 CET
// File:    meta.cpp

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

typedef double* matrix_type;

#ifndef N
    #define N 1000
#endif
#ifndef ITER
    #define ITER 1000
#endif

template<int J>
struct meta_addj {
    inline static void f(const matrix_type & A, const matrix_type & B, matrix_type & C, int const & i, int const & k, double const & temp) {
        C[i * N + J] += temp * B[k * N + J];
        meta_addj<J - 1>::f(A, B, C, i, k, temp);
    }
};

template<>
struct meta_addj<0> {
    inline static void f(const matrix_type A, const matrix_type & B, matrix_type & C, int const & i, int const & k , double const & temp) {
        C[i * N] += temp * B[k * N];
    }
};

void multiply(const matrix_type& A, const matrix_type& B, matrix_type& C) {  
    for(int i = 0; i < N; ++i) {
        for(int k = 0; k < N; ++k) {
            double temp = A[i * N + k];
            meta_addj<N - 1>::f(A, B, C, i, k, temp);
        }
    } 
}

#include "main.cpp"
