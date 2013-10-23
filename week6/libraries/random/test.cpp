// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 02:02:35 CEST
// File:    test.cpp

#include <iostream>
#include "random.hpp"

int main(int argc, char* argv[]) {
    
    dg_random::Generator rnd(42);
    std::cout << dg_random::Generator::max() << std::endl;
    
    return 0;
}

