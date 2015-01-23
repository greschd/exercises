// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 03:30:56 CEST
// File:    thread2_test.cpp

#include "../src/common.hpp"
#include "../src/threaded_v2.hpp"

using namespace diffusion;
using namespace diffusion::threaded_v2;

int main(int argc, char* argv[]) {
    
    count_t mesh_size = 128;
    density_t rho(mesh_size + 2, row_t(mesh_size + 2, 0));
    res_t delta = 2./res_t(mesh_size - 1);
    
    for(count_t i = 1; i < mesh_size + 1; ++i) {
        for(count_t j = 1; j < mesh_size + 1; ++j) {
            if((fabs(delta * res_t(i) - 1.) < 0.5) && (fabs(delta * j - 1) < 0.5)) {
                rho[i][j] = 1;
            }
        }
    }
    
    res_t tau = 0.00001;
    res_t D = 1;
    count_t num_steps(0.5 / tau);
    
    count_t num_threads = 4;
    
    print(rho);
    iter(rho, tau, D, delta, num_steps, num_threads);
    print(rho);
    iter(rho, tau, D, delta, num_steps, num_threads);
    print(rho);
    iter(rho, tau, D, delta, num_steps, num_threads);
    iter(rho, tau, D, delta, num_steps, num_threads);
    print(rho);
    
    return 0;
}
