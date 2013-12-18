/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.1
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>
#include <omp.h>

typedef double* matrix_type;
typedef int index_type;

#ifndef N
    #define N 1024
#endif
#ifndef ITER
    #define ITER 10
#endif
#ifndef R
    #define R 4 
#endif


// handle the case where N is not a power of 2 (i don't implement blocking in this case)
template<bool F>
inline void multiply_template(const matrix_type & A, const matrix_type & B, matrix_type & C) {
    //setting C to zero
    for(index_type i = 0; i < N; ++i) {
        for(index_type j = 0; j < N; ++j) {
            C[i * N + j] = 0;
        }
    }
    
    for(index_type i = 0; i < N; ++i) {
        for(index_type k = 0; k < N; ++k) {
            double temp = A[i * N + k];
            for(index_type j = 0; j < N; ++j) {
                C[i * N + j] += temp * B[k * N + j];
            }
        }
    }
}

// computing the partial matrix product
inline void multiply_part(matrix_type const & A, matrix_type const & D, matrix_type & C, index_type const & I, index_type const & J, index_type const & K) {
    for(index_type i = 0; i < R; ++i) {
        for(index_type k = 0; k < R ; k += 4) {
            double temp0 = A[(i + R * I) * N + k + R * K];
            double temp1 = A[(i + R * I) * N + k + 1 + R * K];
            double temp2 = A[(i + R * I) * N + k + 2 + R * K];
            double temp3 = A[(i + R * I) * N + k + 3 + R * K];
            for(index_type j = 0; j < R ; ++j) {
                C[(i + R * I) * N + j + R * J] += temp0 * D[K * N * R + J * R * R + k * R + j] + temp1 * D[K * N * R + J * R * R + (k + 1) * R + j]
                                                + temp2 * D[K * N * R + J * R * R + (k + 2) * R + j] + temp3 * D[K * N * R + J * R * R + (k + 3) * R + j]; 
            }
        }
    }
}

// use blocking when N is dividible by R
template<>
inline void multiply_template<true>(matrix_type const & A, matrix_type const & B, matrix_type & C) {
    // setting C to zero
    for(index_type i = 0; i < (N * N); ++i) {
        C[i] = 0;
    }
    
    // rearranging the array B so that blocks are continuous in memory (O(N^2))
    matrix_type D = new double[N * N];
    for(index_type i = 0; i < N / R; ++i) {
        for(index_type j = 0; j < N / R; ++j) {
            for(index_type k = 0; k < R; ++k) {
                for(index_type l = 0; l < R; ++l) {
                    D[i * N * R + j * R * R + k * R + l] = B[i * N * R + j * R  + k * N + l];
                }
            }
        }
    }
    
    // multiplying the blocks
    for(index_type i = 0; i < N / R; ++i) {
        #pragma omp parallel for
        for(index_type j = 0; j < N / R; ++j) {
            for(index_type k = 0; k < N / R; ++k) {
                multiply_part(A, D, C, i, j, k);
            }
        }
    }
    delete[] D;
}


inline void multiply(matrix_type const & A, matrix_type const & B, matrix_type & C) {
    multiply_template<((N % R) == 0 && R % 4 == 0)>(A, B, C);
}


#include "main.cpp"
