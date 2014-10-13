// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 02:43:58 CEST
// File:    serial.hpp

#ifndef ___HEADER
#define ___HEADER

#include <vector>
#include <iostream>

typedef int size_t;
typedef double val_t;
typedef std::vector<val_t> density_t;

class DiffusionOMP {
public:
    DiffusionOMP(   size_t const & N, 
                    val_t const & tau,
                    val_t const & D,
                    )   N_(N), 
                        Ntot_(N*N), 
                        rho_(density_t(Ntot_)), 
                        rho2_(density_t(Ntot_)),
                        delta_(2. / (N - 1))
                        f1_(tau * D / (delta_ * delta_)),
                        f2_(1. - 4. * f1_){
        // initialize rho
        for(size_t i = 0; i < N_; ++i) {
            for(size_t j = 0; j < N_; ++j) {
                if((fabs(delta*i - 1.) < 0.5) && (fabs(delta*j - 1.) < 0.5)) {
                    rho[i*N_ + j] = 1;
                }
            }
        }
    }
    
    void iterate(size_t num_steps) {
        for(size_t n = 0; n < num_steps; ++n) {
            for(size_type i = 0; i < N_; ++i) {
                for(size_type j = 0; j < N_; ++j) {
                    rho2_[i*N_ + j] = f2_ * rho_[i*N_ + j] +
                    f1_ * ( (j == N_-1 ? 0. : rho_[i*N_ + (j+1)]) +
                            (j == 0    ? 0. : rho_[i*N_ + (j-1)]) +
                            (i == N_-1 ? 0. : rho_[(i+1)*N_ + j]) +
                            (i == 0    ? 0. : rho_[(i-1)*N_ + j]));
                }
            }
            std::swap(rho2_, rho_);
        }
    }
    
    void print() const{
        for(uint i = 0; i < N_; ++i) {
            for(uint j = 0; j < N_; ++j) {
                std::cout << rho_[i * N_ + j] << " ";
            }
            std::cout << "\\";
        }
    std::cout << "end";
}
    
    
private:
    // size of rho
    size_t N_, Ntot_;

    density_t rho_;
    density_t rho2_;
    
    val_t delta_;
    // tau * D / (delta)^2
    val_t f1_;
    // 1 - 4*f1
    val_t f2_;
};

#endif //___HEADER

