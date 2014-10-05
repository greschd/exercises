// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    05.10.2014 20:22:37 CEST
// File:    diffusion_serial.cpp

#include <cmath>
#include <vector>
#include <iostream>

typedef int count_t;
typedef double res_t;
typedef std::vector<double> row_t;
typedef std::vector<std::vector<res_t>> density_t;

// factor = tau * D / delta^2
// edge values = boundary condition (not updated)
// rho / rho_new of size (n+2)x(m+2)
void iterate (  density_t const & rho, 
                density_t & rho_new, 
                res_t const & factor, 
                count_t const & n,
                count_t const & m, 
                count_t const & n_min,
                count_t const & n_max) {
    
    res_t factor2 = 1 - 4 * factor;
    
    for(count_t i = 1; i < n + 1; ++i) {
        for(count_t j = 1; j < m + 1; ++j) {
            rho_new[i][j] = factor2 * rho[i][j];
        }
    }
    
    // to avoid aliasing issues
    res_t current_value;
    for(count_t i = 1; i < n + 1; ++i) {
        for(count_t j = 1; j < m + 1; ++j) {
            current_value = factor * rho[i][j];
            rho_new[i][j + 1] += current_value;
            rho_new[i][j - 1] += current_value;
            rho_new[i + 1][j] += current_value;
            rho_new[i - 1][j] += current_value;
        }
    }
    
}

void clear_border(  density_t & rho_new, 
                    count_t const & n,
                    count_t const & m, 
                    ) {
    // clear out border (maybe checks are better?)
    // border acts as a heat sink
    for(count_t i = 0; i < n + 2; ++i) {
        rho_new[i][0] = 0;
        rho_new[i][m + 1] = 0;
    }
    for(count_t j = 0; j < m + 2; ++j) {
        rho_new[0][j] = 0;
        rho_new[n + 1][j] = 0;
    }
}

void diffusion( density_t & rho, 
                res_t const & tau,
                res_t const & D,
                res_t const & delta,
                count_t num_steps
                ) {
    
    res_t factor = tau * D / (delta * delta);
    count_t n = rho.size() - 2;
    count_t m = rho[0].size() - 2;
    
    density_t rho_new(n + 2, row_t(m + 2));
    
    for(count_t i = 0; i < num_steps; ++i) {
        iterate(rho, rho_new, factor, n, m);
        rho.swap(rho_new);
    }
    
}

void print( density_t const & rho ) {
    for(uint i = 0; i < rho.size(); ++i) {
        for(uint j = 0; j < rho[i].size(); ++j) {
            std::cout << rho[i][j] << " ";
        }
        std::cout << "\\";
    }
    std::cout << "end";
}

int main(int argc, char* argv[]) {
    
    count_t mesh_size = 256;
    density_t rho(mesh_size + 2, row_t(mesh_size + 2, 0));
    res_t delta = 2./res_t(mesh_size - 1);
    
    for(count_t i = 1; i < mesh_size + 1; ++i) {
        for(count_t j = 1; j < mesh_size + 1; ++j) {
            if((fabs(delta * res_t(i) - 1.) < 0.5) && (fabs(delta * j - 1) < 0.5)) {
                rho[i][j] = 1;
            }
        }
    }
    
    res_t tau = 0.000001;
    res_t D = 1;
    count_t num_steps(0.5 / tau);
    
    print(rho);
    diffusion(rho, tau, D, delta, num_steps);
    print(rho);
    diffusion(rho, tau, D, delta, num_steps);
    print(rho);
    diffusion(rho, tau, D, delta, num_steps);
    diffusion(rho, tau, D, delta, num_steps);
    print(rho);
    
    return 0;
}
