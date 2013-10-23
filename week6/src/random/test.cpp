// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 02:02:35 CEST
// File:    test.cpp

#include <iostream>
#include "random.hpp"

int main(int argc, char* argv[]) {
    
    dg_random<long unsigned int> a(11208);
    for(uint i = 0; i < 100; ++i) {
    std::cout << a.newread() << std::endl;
    }
    
    return 0;
}

