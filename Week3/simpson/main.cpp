// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    04.10.2013 10:01:02 CEST
// File:    main.cpp

#include <iostream>
#include "simpson.hpp"
#include <math.h>

int main(int argc, char* argv[]) {
    int N;
    std::cout << "Enter the number of bins" << std::endl;
    std::cin >> N;
    std::cout << simpson(sin,0,M_PI,N) << std::endl;
    return 0;
}
