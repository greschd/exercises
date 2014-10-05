// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    05.10.2014 20:22:37 CEST
// File:    diffusion_serial.cpp

#include <cmath>
#include <vector>
#include <thread>
#include <iostream>

typedef int count_t;
typedef double res_t;
typedef std::vector<double> row_t;
typedef std::vector<std::vector<res_t>> density_t;

namespace threaded {
    
    // factor = tau * D / delta^2
    // edge values = boundary condition (not updated)
    // rho / rho_new of size (n+2)x(m+2)
    void iterate (  density_t const & rho, 
                    density_t & rho_new, 
                    res_t const & factor, 
                    res_t const & factor2,
                    count_t const & n,
                    count_t const & m, 
                    count_t const & n_lower,
                    count_t const & n_upper) {
        
        for(count_t i = n_lower; i < n_upper; ++i) {
            for(count_t j = 1; j < m + 1; ++j) {
                rho_new[i][j] = factor2 * rho.at(i).at(j) + 
                                factor * rho.at(i - 1).at(j) + 
                                factor * rho.at(i + 1).at(j) + 
                                factor * rho.at(i).at(j - 1) + 
                                factor * rho.at(i).at(j + 1);
            }
        }
    }

    void clear_border(  density_t & rho_new, 
                        count_t const & n,
                        count_t const & m
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
                    count_t num_steps,
                    count_t num_threads
                    ) {
        
        res_t factor = tau * D / (delta * delta);
        res_t factor2 = 1 - 4 * factor;
        count_t n = rho.size() - 2;
        count_t m = rho[0].size() - 2;
        
        // calculate which thread will do which rows
        std::vector<count_t> n_borders(num_threads + 1);
        for(count_t i = 0; i < num_threads ; ++i) {
            n_borders[i] = count_t(1 + i * (n / res_t(num_threads)));
        }
        n_borders[num_threads] = n + 1; // to avoid roundoff errors
        
        // threads vector
        std::vector<std::thread> threads(num_threads);
        
        density_t rho_new(n + 2, row_t(m + 2));
        
        for(count_t i = 0; i < num_steps; ++i) {
            for(count_t j = 0; j < num_threads; ++j) {
                threads[j] = std::thread(   iterate, 
                                            rho, 
                                            std::ref(rho_new), 
                                            factor, 
                                            factor2, 
                                            n, 
                                            m, 
                                            n_borders[j],
                                            n_borders[j + 1]);
            }
            for(std::thread & t: threads) {
                t.join();
            }
            clear_border(rho_new, n, m);
            rho.swap(rho_new);
        }
        
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

bool compare(   density_t const & rho1, 
                density_t const & rho2, 
                res_t const & tolerance) {
    for(uint i = 0; i < rho1.size(); ++i) {
        for(uint j = 0; j < rho1[i].size(); ++j) {
            if(fabs(rho1[i][j] - rho2[i][j]) > tolerance) {
                return false;
            }
        }
    }
    
    return true;
}


