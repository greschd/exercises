// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:15:45 CEST
// File:    compare.cpp

#include "../src/common.hpp"
#include "../src/serial.hpp"
#include "../src/threaded_v1.hpp"

#include <iostream>

using namespace diffusion;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cout << "needs the number of threads as argv" << std::endl;
        return 0;
    }
    
    count_t mesh_size = 128;
    density_t rho_t(mesh_size + 2, row_t(mesh_size + 2, 0));
    density_t rho_s(mesh_size + 2, row_t(mesh_size + 2, 0));
    res_t delta = 2./res_t(mesh_size - 1);
    
    for(count_t i = 1; i < mesh_size + 1; ++i) {
        for(count_t j = 1; j < mesh_size + 1; ++j) {
            if((fabs(delta * res_t(i) - 1.) < 0.5) && (fabs(delta * j - 1) < 0.5)) {
                rho_t[i][j] = 1;
                rho_s[i][j] = 1;
            }
        }
    }
    
    res_t tau = 0.00001;
    res_t D = 1;
    count_t num_steps(0.5 / tau);
    count_t num_threads = atoi(argv[1]);
    serial::iter(rho_s, tau, D, delta, num_steps);
    threaded_v1::iter(rho_t, tau, D, delta, num_steps, num_threads);
    if (compare(rho_s, rho_t, 0.001)) {
        std::cout << "Threaded and Serial implementation have the same result" << std::endl;
    }
    else {
        std::cout << "Results do not match!" << std::endl;
    }
    
    
    return 0;
}
