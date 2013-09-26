// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    25.09.2013 13:20:35 CEST
// File:    simpson.cpp
// PRE:     Input is a non-zero natural number N giving the number of bins (0,Pi) will be split into
// POST:    Output is the integral over (0,Pi) of sin(x) using the Simpson integration rule over N bins.

#include <iostream>
#include <math.h>
#include <assert.h>

inline double func(const double & x){
    return sin(x);
}

int main(int argc, char* argv[]) {
    
    // Input of the number of bins N
    int N;
    std::cout << "How many bins would you like to use?" << std::endl;
    std::cin >> N;
    assert(N > 0);   // I didn't want to use unsigned int because a small negative input would produce huge N
    
    // Optional input of different integration limits (un-comment to use)
    //~ std::cout << "What is the lower integration limit?" << std::endl;
    //~ double a;
    //~ std::cin >> a;
    //~ 
    //~ std::cout << "What is the upper integration limit?" << std::endl;
    //~ double b;
    //~ std::cin >> b;
    //~ assert(b>a);
    
    // Standard integration limits (comment when using different ones)
    const double a(0);
    const double b(M_PI);

    // Computing the step between two bins
    const double step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    double sum(0);
    const double a_new = a + step / 2;
    for(int i = 0; i < N ; ++i){
        sum += func(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(int j = 1; j < N; ++j){
        sum += func(a + j * step);
        }
    
    // Adding the boundaries
    sum += (func(a) + func (b)) / 2;
    
    // Output and adding the prefactor step / 3
    std::cout << "The integral of sin(x) from x = " << a << " to x = " <<  b << " is = " << sum * step / 3 << std::endl; 
    
    return 0;
}
