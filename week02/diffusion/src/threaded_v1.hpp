// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    05.10.2014 20:22:37 CEST
// File:    threaded_v1.hpp

// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 02:42:49 CEST
// File:    threaded_v1.hpp

#ifndef _THREADED_V1__HEADER
#define _THREADED_V1__HEADER

#include "common.hpp"

#include <cmath>
#include <vector>
#include <thread>
#include <iostream>

namespace diffusion {
        
    namespace threaded_v1 {
        
        // factor = tau * D / delta^2
        // edge values = boundary condition (not updated)
        // rho / rho_new of size (n+2)x(m+2)
        void single_iter (  density_t const & rho, 
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

        void iter( density_t & rho, 
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
            
            for(count_t i = 0; i < num_steps; ++i) {
                for(count_t j = 0; j < num_threads - 1; ++j) {
                    threads[j] = std::thread(   single_iter, 
                                                rho, 
                                                std::ref(rho_new), 
                                                factor, 
                                                factor2, 
                                                n, 
                                                m, 
                                                n_borders[j],
                                                n_borders[j + 1]);
                }
                // compute in main thread
                single_iter(rho, rho_new, factor, factor2, n, m, n_borders[num_threads - 1], n_borders[num_threads]);
                for(std::thread & t: threads) {
                    t.join();
                }
                rho.swap(rho_new);
            }
            
        }
        
    } // namespace threaded_v1
}// namespace diffusion

#endif //_THREADED_V1__HEADER
