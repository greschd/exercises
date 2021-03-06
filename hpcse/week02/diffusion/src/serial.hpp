// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 02:43:58 CEST
// File:    serial.hpp

#ifndef ___HEADER
#define ___HEADER

#include "common.hpp"

#include <vector>
#include <iostream>

namespace diffusion {
    namespace serial {
        // factor = tau * D / delta^2
        // edge values = boundary condition (not updated)
        // rho / rho_new of size (n+2)x(m+2)
        inline void single_iter (   density_t const & rho, 
                                    density_t & rho_new, 
                                    res_t const & factor,
                                    res_t const & factor2, 
                                    count_t const & n,
                                    count_t const & m) {
            
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

        void iter(  density_t & rho, 
                    res_t const & tau,
                    res_t const & D,
                    res_t const & delta,
                    count_t num_steps
                    ) {
            res_t factor = tau * D / (delta * delta);
            res_t factor2 = 1 - 4 * factor;
            count_t n = rho.size() - 2;
            count_t m = rho[0].size() - 2;
            
            density_t rho_new(n + 2, row_t(m + 2));
            
            for(count_t i = 0; i < num_steps; ++i) {
                single_iter(rho, rho_new, factor, factor2, n, m);
                rho.swap(rho_new);
            }
            
        }

    } // namespace serial
} // namespace diffusion

#endif //___HEADER

