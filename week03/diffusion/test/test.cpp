// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 00:37:45 CEST
// File:    serial_test.cpp

#include "../src/diffusion_omp.hpp"

#include <cmath>
#include <iostream>


int main(int argc, char* argv[]) {
    
    count_t mesh_size = 128;
    val_t tau = 0.00001;
    val_t D = 1;
    
    DiffusionOMP system(mesh_size, tau, D);
    
    count_t num_steps(0.5 / tau);
    system.print();
    system.iterate(num_steps);    
    system.print();
    system.iterate(num_steps);    
    system.print();
    system.iterate(num_steps);    
    system.iterate(num_steps);    
    system.print();
    
    return 0;
}
