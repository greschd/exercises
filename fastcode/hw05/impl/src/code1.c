#ifndef NB
#error NB is not defined
#endif

#define MU 2
#define NU 2
#define KU 1

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//register blocking
void compute() {
    int i, j, k;
    double c00, c01, c10, c11;
    for(i = 0; i < NB; i += MU) {
        for(j = 0; j < NB; j += NU) {
            for(k = 0; k < NB ; ++k) {
                c00 = A[i * NB + k] * B[k * NB + j];
                c01 = A[i * NB + k] * B[k * NB + (j + 1)];
                c10 = A[(i + 1) * NB + k] * B[k * NB + j];
                c11 = A[(i + 1) * NB + k] * B[k * NB + j + 1];
                
                C[i * NB + j] += c00;
                C[i * NB + j + 1] += c01;
                C[(i + 1) * NB + j] += c10;
                C[(i + 1) * NB + j + 1] += c11;
            }
        }
    }
}

