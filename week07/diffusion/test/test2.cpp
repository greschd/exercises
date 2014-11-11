// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 00:37:45 CEST
// File:    serial_test.cpp

#include "../src/diffusion_omp.hpp"

#include <cmath>
#include <iostream>


int main(int argc, char* argv[]) {
    
    count_t mesh_size = 128;
    val_t tau = 0.00001;
    val_t D = atoi(argv[1]);
    
    DiffusionOMP system(mesh_size, tau, D);
    
    count_t num_steps(0.5 / tau);
    for(uint i = 0; i < 21; ++i) {
        std::cout << 0.5 * i << ", " << system.N() << ", " << system.musquare() << std::endl;
        system.iterate(num_steps);
    }
    
    return 0;
}
