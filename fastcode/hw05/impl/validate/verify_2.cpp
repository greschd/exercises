// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.04.2014 16:10:15 CEST
// File:    verification.cpp

#include "../src/code2.c"

#include <iostream>
#include <random>
#include <ctime>
#include <cassert>

double* Cref;
std::mt19937 rng(std::time(NULL));
std::uniform_real_distribution<double> distr;


#define VERIFY		 													\
A = (double*)malloc(NB*NB*sizeof(double));								\
B = (double*)malloc(NB*NB*sizeof(double));								\
C = (double*)malloc(NB*NB*sizeof(double));								\
Cref = (double*)malloc(NB*NB*sizeof(double));							\
for(uint i = 0; i < NB; ++i) {											\
	for(uint j = 0; j < NB; ++j) {										\
		A[i * NB + j] = distr(rng);										\
		B[i * NB + j] = distr(rng);										\
		C[i * NB + j] = distr(rng);										\
		Cref[i * NB + j] = C[i * NB + j];								\
	}																	\
}																		\
compute();																\
for(uint i = 0; i < NB; ++i) {											\
	for(uint j = 0; j < NB; ++j) {										\
		for(uint k = 0; k < NB; ++k) {									\
			Cref[i * NB + j] += A[i * NB + k] * B[k * NB + j];			\
		}																\
	}																	\
}																		\
for(uint i = 0; i < NB; ++i) {											\
	for(uint j = 0; j < NB; ++j) {										\
		assert(fabs(C[i * NB + j] - Cref[i * NB + j]) < 1e-7);			\
	}																	\
}																		\


int main(int argc, char* argv[]) {
	VERIFY;
	return 0;
}
