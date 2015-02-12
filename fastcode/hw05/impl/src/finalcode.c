#ifndef N
#error N is not defined
#endif

#define NB 86
#define MU 2
#define NU 2
#define KU 2

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being N x N matrices
void compute() {
    int i, j, k, i2, j2, k2;
    double c000, c001, c010, c011, c100, c101, c110, c111;
    for(i = 0; i < N; i+=NB) {
        for(j = 0; j < N; j+=NB) {
            for(k = 0; k < N; k+=NB) {
                for(i2 = i; i2 < (i + NB); i2 += MU) {
                    for(j2 = j; j2 < (j + NB); j2 += NU) {
                        for(k2 = k; k2 < (k + NB); k2 += KU) {
                            c000 = A[i2 * N + k2] * B[k2 * N + j2];
                            c001 = A[i2 * N + k2] * B[k2 * N + (j2 + 1)];
                            c010 = A[(i2 + 1) * N + k2] * B[k2 * N + j2];
                            c011 = A[(i2 + 1) * N + k2] * B[k2 * N + j2 + 1];
                            c100 = A[i2 * N + k2 + 1] * B[(k2 + 1) * N + j2];
                            c101 = A[i2 * N + k2 + 1] * B[(k2 + 1) * N + (j2 + 1)];
                            c110 = A[(i2 + 1) * N + k2 + 1] * B[(k2 + 1) * N + j2];
                            c111 = A[(i2 + 1) * N + k2 + 1] * B[(k2 + 1) * N + j2 + 1];
                            
                            C[i2 * N + j2] += c000 + c100;
                            C[i2 * N + j2 + 1] += c001 + c101;
                            C[(i2 + 1) * N + j2] += c010 + c110;
                            C[(i2 + 1) * N + j2 + 1] += c011 + c111;
                        }
                    }
                }
            }
        }
    }
}

