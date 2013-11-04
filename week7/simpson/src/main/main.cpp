// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    04.10.2013 10:01:02 CEST
// File:    main.cpp
// PRE:     Input are the lower and upper integration limits a,b and the number of bins N
// POST:    Output is the Simpson integral of sin(x) over (a,b) using N bins. 

#include <iostream>
#include <simpson.hpp>
#include <math.h>
#include <mysin.hpp>

int main(int argc, char* argv[]) {
    
    // Input
    int N;
    double a, b, lambda;
    
    std::cout << "We want to compute the Simpson integral from x=a to x=b of sin(lambda*x) using N bins" << std::endl;
    
    std::cout << "a = ?" << std::endl;
    std::cin >> a;

    std::cout << "b = ?" << std::endl;    
    std::cin >> b;
    
    std::cout << "N = ?" << std::endl;
    std::cin >> N;
    
    std::cout << "lambda = ?" << std::endl;
    std::cin >> lambda;
    
    mysin sinlambda(lambda);
    
    //Output
    std::cout << "The integral is I = " << simpson<mysin>(sinlambda, a, b, N) << std::endl;
    return 0;
}
