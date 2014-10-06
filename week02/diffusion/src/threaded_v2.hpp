// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 03:31:53 CEST
// File:    threaded_v2.hpp

#ifndef __THREADED_V2_HEADER
#define __THREADED_V2_HEADER


#include "common.hpp"
#include "../../barrier/barrier.hpp"

#include <cmath>
#include <vector>
#include <thread>
#include <iostream>

using namespace barrier;

namespace diffusion {
        
    namespace threaded_v2 {
        
        // factor = tau * D / delta^2
        // edge values = boundary condition (not updated)
        // rho / rho_new of size (n+2)x(m+2)
        void iter_thread (  density_t & rho, 
                            density_t & rho_new, 
                            barrier_cl & b,
                            res_t const & factor, 
                            res_t const & factor2,
                            count_t const & num_steps,
                            count_t const & n,
                            count_t const & m, 
                            count_t const & n_lower,
                            count_t const & n_upper) {
            
            for(count_t k = 0; k < num_steps; ++k) {
                // avoid the swap
                if(k % 2 == 0) {
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
                else {
                    for(count_t i = n_lower; i < n_upper; ++i) {
                        for(count_t j = 1; j < m + 1; ++j) {
                            rho[i][j] = factor2 * rho_new.at(i).at(j) + 
                                        factor * rho_new.at(i - 1).at(j) + 
                                        factor * rho_new.at(i + 1).at(j) + 
                                        factor * rho_new.at(i).at(j - 1) + 
                                        factor * rho_new.at(i).at(j + 1);
                        }
                    }
                    
                }
                
                b.wait();
            }
        }

        void iter(  density_t & rho, 
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
            std::vector<std::thread> threads(num_threads - 1);
            
            density_t rho_new(n + 2, row_t(m + 2));
            barrier_cl b(num_threads);
            
            for(count_t j = 0; j < num_threads - 1; ++j) {
                threads[j] = std::thread(   iter_thread, 
                                            std::ref(rho), 
                                            std::ref(rho_new), 
                                            std::ref(b),
                                            factor, 
                                            factor2, 
                                            num_steps,
                                            n, 
                                            m, 
                                            n_borders[j],
                                            n_borders[j + 1]);
            }
            // compute in main thread
            iter_thread(rho, rho_new, b, factor, factor2, num_steps, n, m, n_borders[num_threads - 1], n_borders[num_threads]);
            for(std::thread & t: threads) {
                t.join();
            }
        }
        
    } // namespace threaded_v2
} // namespace diffusion

#endif //__THREADED_V2_HEADER
