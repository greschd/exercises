/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.1
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

typedef double* matrix_type;
typedef uint16_t index_type;

#ifndef N
    #define N 1024
#endif
#ifndef ITER
    #define ITER 10
#endif
#ifndef R
    #define R 1
#endif


// handle the case where N is not a power of 2 (i don't implement blocking in this case)
template<bool F>
void multiply_template(const matrix_type & A, const matrix_type & B, matrix_type & C) {
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

// computing the partial matrix sum
inline void multiply_part(matrix_type const & A, matrix_type const & B, matrix_type & C, index_type const & I, index_type const & J, index_type const & K) {
    for(index_type i = 0; i < R; ++i) {
        for(index_type k = 0; k < R; ++k) {
            double temp = A[(i +  R * I)* N + k + (R * K)];
            for(index_type j = 0; j < R; ++j) {
                C[(i + R * I) * N + j + R * J] += temp * B[K * N * R + J * R * R + k * R + j]; 
            }
        }
    }
}

// use blocking when N is dividible by R
template<>
void multiply_template<true>(matrix_type const & A, matrix_type const & B, matrix_type & C) {
    // setting C to zero
    for(index_type i = 0; i < N; ++i) {
        for(index_type j = 0; j < N; ++j) {
            C[i * N + j] = 0;
        }
    }
    
    // rearranging the arrays B so that blocks are continuous in memory (O(N^2))
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
    
    for(index_type i = 0; i < N / R; ++i) {
        for(index_type j = 0; j < N / R; ++j) {
            for(index_type k = 0; k < N / R; ++k) {
                multiply_part(A, D, C, i, j, k);
            }
        }
    }
    delete[] D;
}


inline void multiply(matrix_type const & A, matrix_type const & B, matrix_type & C) {
    multiply_template<(N % R) == 0>(A, B, C);
}


#include "main.cpp"
