// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 11:53:14 CET
// File:    test_s.cpp


#include "../src/common.hpp"
#include "../src/vortex_serial.hpp"

#include <iostream>


val_t gamma(val_t x) {
    return x*x;
}

int main(int argc, char* argv[]) {

    
    VortexSheet_S test(10000, gamma);
    test.print();
    for(uint i = 0; i < 20; ++i) {
        test.iterate(10, 0.01);
        test.print();
    }
    
    return 0;
}
