// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    06.12.2013 17:11:19 CET
// File:    main.cpp

#ifndef __MAIN_FILE
#define __MAIN_FILE

#ifndef TESTING
    #define TESTING false
#endif 

void set(matrix_type& A, matrix_type& B)
{
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j){
            A[i * N + j] = drand48();
            B[i * N + j] = drand48();
        }
    }
}

void print(const matrix_type& A) {
  for(int i=0; i<N; ++i){

    for(int j=0; j<N; ++j)
      std::cout << A[i * N + j] << " ";

    std::cout << std::endl;
  }
}

int main() 
{
    const int num_iter = ITER;
    
    matrix_type A = new double [N*N];
    matrix_type B = new double [N*N];
    matrix_type C = new double [N*N];
    
    set(A, B);
    
    /*------------------------------*/
    /*            timing            */
    /*------------------------------*/
    
    if(!TESTING) {
        timeval start, end;
        gettimeofday(&start, NULL);
        
        for (int i = 0; i < num_iter ; ++i) {
            multiply(A, B, C);
        }
        
        gettimeofday(&end, NULL);
        
        std::cout << "size: " << N << ", time: " << (end.tv_sec - start.tv_sec)+1e-6*(end.tv_usec - start.tv_usec) << std::endl;
    }
    
    
    /*------------------------------*/
    /*            testing           */
    /*------------------------------*/
    if(TESTING) {
        multiply(A, B, C);
        
        std::cout << "A: " << std::endl;
        print(A);
        
        std::cout << "B: " << std::endl;
        print(B);
        
        std::cout << "C:" << std::endl;
        print(C);
    }

    delete[] A;
    delete[] B;
    delete[] C;
    
    return 0;
}


#endif //__MAIN_FILE

