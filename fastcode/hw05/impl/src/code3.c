#ifndef NB
#error NB is not defined
#endif

#define MU 1
#define NU 8
#define KU 2

double *A, *B, *C;

//The following code implements C = A B + C
//with A, B and C being NB x NB matrices
//unrolling 4
void compute() {
    int i, j, k;
    double c00, c01, c10, c11, c20, c21, c30, c31, c40, c41, c50, c51, c60, c61, c70, c71;
    for(i = 0; i < NB; i += MU) {
        for(j = 0; j < NB; j += NU) {
            for(k = 0; k < NB ; k += KU) {
                c00 = A[i * NB + k] * B[k * NB + j];
                c10 = A[i * NB + k] * B[k * NB + j + 1];
                c20 = A[i * NB + k] * B[k * NB + j + 2];
                c30 = A[i * NB + k] * B[k * NB + j + 3];
                c40 = A[i * NB + k] * B[k * NB + j + 4];
                c50 = A[i * NB + k] * B[k * NB + j + 5];
                c60 = A[i * NB + k] * B[k * NB + j + 6];
                c70 = A[i * NB + k] * B[k * NB + j + 7];

                c01 = A[i * NB + k + 1] * B[(k + 1) * NB + j];
                c11 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 1];
                c21 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 2];
                c31 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 3];
                c41 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 4];
                c51 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 5];
                c61 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 6];
                c71 = A[i * NB + k + 1] * B[(k + 1) * NB + j + 7];

                C[i * NB + j] += c00 + c01;
                C[i * NB + j + 1] += c10 + c11;
                C[i * NB + j + 2] += c20 + c21;
                C[i * NB + j + 3] += c30 + c31;
                C[i * NB + j + 4] += c40 + c41;
                C[i * NB + j + 5] += c50 + c51;
                C[i * NB + j + 6] += c60 + c61;
                C[i * NB + j + 7] += c70 + c71;
            }
        }
    }
}
