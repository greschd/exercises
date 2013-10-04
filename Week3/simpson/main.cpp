// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    04.10.2013 10:01:02 CEST
// File:    main.cpp
// PRE:     Input are the lower and upper integration limits a,b and the number of bins N
// POST:    Output is the Simpson integral of sin(x) over (a,b) using N bins. 

#include <iostream>
#include "simpson.hpp"
#include <math.h>

int main(int argc, char* argv[]) {
    
    // Input
    int N;
    double a, b;
    std::cout << "What is the lower integration limit?" << std::endl;
    std::cin >> a;
    
    std::cout << "What is the upper integration limit?" << std::endl;
    std::cin >> b;
    
    std::cout << "Enter the number of bins" << std::endl;
    std::cin >> N;
    
    //Output
    std::cout << simpson(sin,a,b,N) << std::endl;
    return 0;
}
