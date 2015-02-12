// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.04.2014 16:10:15 CEST
// File:    verification.cpp

#include "../src/finalcode.c"

#include <iostream>
#include <random>
#include <ctime>
#include <cassert>

double* Cref;
std::mt19937 rng(std::time(NULL));
std::uniform_real_distribution<double> distr;


#define VERIFY                                                          \
A = (double*)malloc(N*N*sizeof(double));                                \
B = (double*)malloc(N*N*sizeof(double));                                \
C = (double*)malloc(N*N*sizeof(double));                                \
Cref = (double*)malloc(N*N*sizeof(double));                         \
for(uint i = 0; i < N; ++i) {                                           \
    for(uint j = 0; j < N; ++j) {                                       \
        A[i * N + j] = distr(rng);                                      \
        B[i * N + j] = distr(rng);                                      \
        C[i * N + j] = distr(rng);                                      \
        Cref[i * N + j] = C[i * N + j];                             \
    }                                                                   \
}                                                                       \
compute();                                                              \
for(uint i = 0; i < N; ++i) {                                           \
    for(uint j = 0; j < N; ++j) {                                       \
        for(uint k = 0; k < N; ++k) {                                   \
            Cref[i * N + j] += A[i * N + k] * B[k * N + j];             \
        }                                                               \
    }                                                                   \
}                                                                       \
for(uint i = 0; i < N; ++i) {                                           \
    for(uint j = 0; j < N; ++j) {                                       \
        assert(fabs(C[i * N + j] - Cref[i * N + j]) < 1e-7);            \
    }                                                                   \
}                                                                       \


int main(int argc, char* argv[]) {
    VERIFY;
    return 0;
}
