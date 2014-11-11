// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing.cpp

#ifndef __TIMING_HEADER
#define __TIMING_HEADER



#include "../src/diffusion_omp.hpp"

#include <chrono>
#include <iostream>


double timing(  count_t const & mesh_size, 
                val_t const & tau, 
                val_t const & D) {
    
    
    DiffusionOMP system(mesh_size, tau, D);
    count_t num_steps = 1e9 / (mesh_size * mesh_size);
    
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // start clock
    start = std::chrono::high_resolution_clock::now();
    system.iterate(num_steps);
    // end clock
    end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main(int argc, char* argv[]) {
    
    count_t mesh = 128;
    val_t tau = 0.00001;
    val_t D(atoi(argv[1]));
    
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, D) << std::endl;
    mesh = 256;
    tau = 0.000001;
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, D) << std::endl;
    mesh = 1024;
    tau = 0.00000001;
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, D) << std::endl;
    
    return 0;
}


#endif //__TIMING_HEADER
