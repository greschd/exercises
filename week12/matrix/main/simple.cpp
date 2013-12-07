/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.1
 */

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

void multiply(const matrix_type& A, const matrix_type& B, matrix_type& C) {   
    //setting C to zero
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            C[i * N + j] = 0;
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int k = 0; k < N; ++k) {
            double temp = A[i * N + k];
            for(int j = 0; j < N; ++j) {
                C[i * N + j] += temp * B[k * N + j];
            }
        }
    }
}

#include "main.cpp"
