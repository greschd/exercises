/* Programming Techniques for Scientific Simulations, HS 2013
 * Exercise 12.1
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

typedef std::vector<double> matrix_type;

#define N 1000

void set(matrix_type& A, matrix_type& B)
{
  for (int i=0; i<N; ++i)
    for (int j=0; j<N; ++j){
      A[i*N+j] = drand48();
      B[i*N+j] = drand48();
    }
}

template<int J>
struct meta_addj {
    template<int I, int K>
    static void f(double temp, matrix_type & B, matrix_type & C) {
        C[I * N + J] += temp * B[K * N + J];
        meta_addj<J - 1>::f(temp, B, C);
    }
};

template<>
stuct meta_addj<0> {
    template<int I, int K>
    static void f(double temp, matrix_type & B, matrix_type & C) {
        C[I * N] += temp * B[K * N];
    }
};

void multiply_simple(const matrix_type& A, const matrix_type& B, matrix_type& C)
{
    for(int i = 0; i < N; ++i) {
        for(int k = 0; k < N; ++k) {
            double temp = A[i * N + k];
            for(int j = 0; j < N; ++j) {
                C[i * N + j] += temp * B[k * N + j];
            }
        }
    }
}

void print(const matrix_type& A)
{
  for(int i=0; i<N; ++i){

    for(int j=0; j<N; ++j)
      std::cout << A[i*N+j] << " ";

    std::cout << std::endl;
  }
}

int main() 
{
    const int num_iter = 5;
    
    matrix_type A(N*N), B(N*N), C(N*N);
    
    set(A, B);
    
    /*------------------------------*/
    /*            timing            */
    /*------------------------------*/
    timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < num_iter; ++i) {
        multiply_simple(A, B, C);
    }
    
    gettimeofday(&end, NULL);
    
    std::cout << N << " " << (end.tv_sec - start.tv_sec)+1e-6*(end.tv_usec - start.tv_usec) << std::endl;
    
    /*------------------------------*/
    /*            testing           */
    /*------------------------------*/
    //~ multiply_simple(A, B, C);
    //~ 
    //~ std::cout << "A: " << std::endl;
    //~ print(A);
    //~ 
    //~ std::cout << "B: " << std::endl;
    //~ print(B);
    //~ 
    //~ std::cout << "C:" << std::endl;
    //~ print(C);

    return 0;
}
