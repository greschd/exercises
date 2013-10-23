// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 02:02:35 CEST
// File:    test.cpp

#include <iostream>
#include "random.hpp"

int main(int argc, char* argv[]) {
    
    dg_random_gen a (1221341);
    for(uint i = 0; i < 10000; ++i) {
    std::cout << a.generatesmall() << std::endl;
    }
    
    return 0;
}

