/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.2
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

typedef double* matrix_type;

#define N 1000

void set(matrix_type& A, matrix_type& B)
{
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j){
            A[i * N + j] = drand48();
            B[i * N + j] = drand48();
        }
    }
}

extern "C" {
    void dgemm_(char const & TRANSA, char const & TRANSB, int const & M,
    int const & SIZE, int const & K, double const & alpha, double * A, int const & LDA,
    double * B, int const & LDB, double const & beta, double* C, int const & LDC);
}

void print(const matrix_type& A)
{
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j) {
            std::cout << A[i*N+j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() 
{
    const int num_iter = 5;

    matrix_type A = new double [N*N];
    matrix_type B = new double [N*N];
    matrix_type C = new double [N*N];
    
    set(A, B);
    
    /*------------------------------*/
    /*            timing            */
    /*------------------------------*/
    timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < num_iter; ++i) {
        dgemm_('n', 'n', N, N, N, 1, B, N, A, N, 0, C, N); // switch A and B to account for Fortran matrix storing
    }
    
    gettimeofday(&end, NULL);
    
    std::cout << N << " " << (end.tv_sec - start.tv_sec)+1e-6*(end.tv_usec - start.tv_usec) << std::endl;
    
    //~ /*------------------------------*/
    //~ /*            testing           */
    //~ /*------------------------------*/
    //~ dgemm_('n', 'n', N, N, N, 1, B, N, A, N, 0, C, N);
    //~ 
    //~ std::cout << "A: " << std::endl;
    //~ print(A);
    //~ 
    //~ std::cout << "B: " << std::endl;
    //~ print(B);
    //~ 
    //~ std::cout << "C:" << std::endl;
    //~ print(C);
    
    delete [] A;
    delete [] B;
    delete [] C;
  return 0;
}
