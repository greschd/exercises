#ifndef NB
#error NB is not defined
#endif

double *A, *B, *C;

//The following code implements C = A B + C 
//with A, B and C being NB x NB matrices
//This is done by definition
void compute() {
        int i, j, k;
    double temp;
    for(i = 0; i < NB; ++i) {
        for(j = 0; j < NB; ++j) {
            temp = 0; 
            for(k = 0; k < NB; ++k) {
                temp += A[i * NB + k] * B[k * NB + j];
            }
            C[i * NB + j] += temp;
        }
    }
}

