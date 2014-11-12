// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 02:43:58 CEST
// File:    diffusion_mpi.hpp

#ifndef __DIFFUSION_MPI_HEADER
#define __DIFFUSION_MPI_HEADER

#include <mpi.h>
#include <cmath>
#include <vector>
#include <iostream>

typedef int count_t;
typedef double val_t;
typedef std::vector<val_t> row_t;
typedef std::vector<row_t> density_t;

template<typename T>
class Accumulator {
    using res_t = decltype(T() / double());
public:
    Accumulator(): res_(0), square_(0) {};

    void operator<<(T const & t) {
        res_ += t;
        square_ += t * t;
        ++N_;
    }

    res_t avg() const {
        return res_ / double(N_);
    }

    res_t square() const {
        return square_ / double(N_);
    }

    auto res() const {
        return std::pair<res_t, res_t>(avg(), square());
    }
    
private:
    T res_;
    T square_;
    count_t N_;
};

class DiffusionMPI {
public:
    DiffusionMPI(   density_t const & rho,
                    val_t const & tau,
                    val_t const & D,
                    count_t const & rank,
                    count_t const & size
                    ):
                        M_(),
                        N_(rho[0].size()), 
                        rho_(),
                        rho2_(),
                        delta_(2. / (rho.size() - 1)),
                        f1_(tau * D / (delta_ * delta_)),
                        f2_(1. - 4. * f1_),
                        n_(),
                        u_sq_(){
        // get upper / lower bounds
        count_t full_M = rho.size();
        count_t lower = (rank * full_M) / size;
        count_t upper = ((rank + 1) * full_M) / size;
        // size will be + 2 for ghost rows
        M_ = (upper - lower) + 2;
        
        // initialize rho
        rho_.push_back(lower == 0 ? rho[full_M - 1] : rho[lower - 1]);
        for(count_t i = lower; i < upper; ++i) {
            rho_.push_back(rho[i]);
        }
        rho_.push_back(upper == full_M ? rho[0] : rho[upper]);
    }
    
    void iterate() {
        for(count_t i = 1; i < M_ - 1; ++i) {
            for(count_t j = 0; j < N_; ++j) {
                rho2_[i][j] = f2_ * rho_[i][j] +
                f1_ * ( (j == N_ - 1 ? 0. : rho_[i][j + 1]) +
                        (j == 0 ? 0. : rho_[i][j - 1]) +
                        rho_[i + 1][j]) + rho_[i - 1][j]));
            }
        }
        std::swap(rho2_, rho_);
    }
    
    void print() const{
        for(count_t i = 0; i < N_; ++i) {
            for(count_t j = 0; j < N_; ++j) {
                std::cout << rho_[i * N_ + j] << " ";
            }
            std::cout << "\\";
        }
        std::cout << "end";
    }
    
    void measure() {
        val_t res_n(0);
        val_t res_u_sq(0);
        for(count_t i = 0; i < N_; ++i) {
            for(count_t j = 0; j < N_; ++j) {
                res_n += rho_[i*N_ + j];
                res_u_sq +=  rho_[i*N_ + j] * 
                             ((i * delta_ - 1.) * (i * delta_ - 1.) +
                             (j * delta_ - 1.) * (j * delta_ - 1.)); 
            }
        }
        n_ << res_n;
        u_sq_ << res_u_sq;
    }

    auto n() const {
        return n_.res();
    }
    
    auto u_sq() const {
        return u_sq_.res();
    }
    
private:
    // size of rho
    count_t M_, N_;

    density_t rho_;
    density_t rho2_;
    
    val_t delta_;
    // tau * D / (delta)^2
    val_t f1_;
    // 1 - 4*f1
    val_t f2_;

    // results
    Accumulator<val_t> n_;
    Accumulator<val_t> u_sq_;
};

#endif //__DIFFUSION_MPI_HEADER

