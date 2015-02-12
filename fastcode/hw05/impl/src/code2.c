#ifndef NB
#error NB is not defined
#endif

#define MU 2
#define NU 2
#define KU 2

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//register blocking
void compute() {
    int i, j, k;
    double c000, c001, c010, c011, c100, c101, c110, c111;
    for(i = 0; i < NB; i += MU) {
        for(j = 0; j < NB; j += NU) {
            for(k = 0; k < NB ; k += KU) {
                c000 = A[i * NB + k] * B[k * NB + j];
                c001 = A[i * NB + k] * B[k * NB + (j + 1)];
                c010 = A[(i + 1) * NB + k] * B[k * NB + j];
                c011 = A[(i + 1) * NB + k] * B[k * NB + j + 1];
                c100 = A[i * NB + k + 1] * B[(k + 1) * NB + j];
                c101 = A[i * NB + k + 1] * B[(k + 1) * NB + (j + 1)];
                c110 = A[(i + 1) * NB + k + 1] * B[(k + 1) * NB + j];
                c111 = A[(i + 1) * NB + k + 1] * B[(k + 1) * NB + j + 1];
                
                C[i * NB + j] += c000 + c100;
                C[i * NB + j + 1] += c001 + c101;
                C[(i + 1) * NB + j] += c010 + c110;
                C[(i + 1) * NB + j + 1] += c011 + c111;
            }
        }
    }
}
