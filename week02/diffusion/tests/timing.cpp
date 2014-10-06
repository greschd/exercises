// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing.cpp

#ifndef __TIMING_HEADER
#define __TIMING_HEADER



#include "../src/common.hpp"

#include <chrono>
#include <iostream>

using namespace diffusion;

double timing(  count_t const & mesh_size, 
                res_t const & tau, 
                count_t const & num_threads) {
    
    density_t rho_t(mesh_size + 2, row_t(mesh_size + 2, 0));
    res_t delta = 2./res_t(mesh_size - 1);
    
    for(count_t i = 1; i < mesh_size + 1; ++i) {
        for(count_t j = 1; j < mesh_size + 1; ++j) {
            if((fabs(delta * res_t(i) - 1.) < 0.5) && (fabs(delta * j - 1) < 0.5)) {
                rho_t[i][j] = 1;
            }
        }
    }
    
    res_t D = 1;
    count_t num_steps = 1e9 / (mesh_size * mesh_size);
    
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // start clock
    start = std::chrono::high_resolution_clock::now();
    FUNCTION_CALL;
    // end clock
    end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main(int argc, char* argv[]) {
    
    count_t num_threads = atoi(argv[1]);
    std::cout << "num_threads: " << num_threads << std::endl;
    
    count_t mesh = 128;
    res_t tau = 0.00001;
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, num_threads) << std::endl;
    mesh = 256;
    tau = 0.000001;
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, num_threads) << std::endl;
    mesh = 1024;
    tau = 0.00000001;
    std::cout << "mesh: " << mesh << ", tau: " << tau << ", time: " << timing(mesh, tau, num_threads) << std::endl;
    
    return 0;
}


#endif //__TIMING_HEADER
