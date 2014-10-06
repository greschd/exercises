// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 02:32:55 CEST
// File:    common.hpp


#ifndef _COMMON__HEADER
#define _COMMON__HEADER

#include <cmath>
#include <vector>
#include <iostream>

namespace diffusion {

    typedef int count_t;
    typedef double res_t;
    typedef std::vector<double> row_t;
    typedef std::vector<std::vector<res_t>> density_t;

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
}
#endif //_COMMON__HEADER
