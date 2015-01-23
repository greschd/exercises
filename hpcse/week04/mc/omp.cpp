// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    18.10.2014 01:18:34 CEST
// File:    serial.cpp

#include <omp.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>
#include <iostream>

typedef double res_t;
typedef int count_t;
typedef std::mt19937_64 rng_t;
const res_t pi = 3.141592653589732;

class MCIntegrator {
public:
    MCIntegrator(   res_t const & x,
                    res_t const & y,
                    res_t const & d,
                    count_t const & seed):
                    x_(x),
                    y_(y),
                    d_(d),
                    sum_(0),
                    squaresum_(0),
                    count_(0),
                    seed_rng_(seed),
                    dist_(0,1),
                    seed_dist_(),
                    thread_rng_vec_()
                    {}

    void measure_paths(count_t const & num_iter) {
        res_t sum(0);
        res_t squaresum(0);
        count_t count(0);
        // heating up the RNG
        for(uint i = 0; i < 100; ++i) {
            seed_dist_(seed_rng_);
        }
        // creating all the RNGs
        #pragma omp parallel 
        {
            res_t xtemp(x_);
            res_t ytemp(y_);
            res_t a;
            // i need this part in parallel to get num_threads
            #pragma omp single
            {
                for(count_t i = 1; i < omp_get_num_threads(); ++i) {
                    thread_rng_vec_.push_back(rng_t(seed_dist_(seed_rng_)));
                }
                thread_rng_vec_.push_back(seed_rng_);
            }

            #pragma omp for reduction(+: sum, squaresum, count)
            for(count_t i = 0; i < num_iter; ++i) {
                // check if (xtemp, ytemp) is still in [0,1]^2
                while(0 < xtemp && xtemp < 1 && 0 < ytemp && ytemp < 1) {
                    a = dist_(thread_rng_vec_[omp_get_thread_num()]);
                    xtemp += d_ * std::cos(2. * pi * a);
                    ytemp += d_ * std::sin(2. * pi * a);
                }
                // accumulate results in res_
                ++count;
                sum += xtemp;
                squaresum += xtemp * xtemp;
                xtemp = x_;
                ytemp = y_;
            }
        }
        sum_ += sum;
        squaresum_ += squaresum;
        count_ += count;
    }

    res_t rho() const {
        return sum_ / count_;
    }

    res_t var() const {
        return (squaresum_  - (sum_ * sum_ / count_)) / (count_ - 1);
    }

    void print() const {
        std::cout << count_ << ", " << rho() << ", " << var() << std::endl;
    }
    
private:
    const res_t x_;
    const res_t y_;
    const res_t d_;
    res_t sum_;
    res_t squaresum_;
    count_t count_;
    rng_t seed_rng_;
    std::uniform_real_distribution<res_t> dist_;
    std::uniform_int_distribution<count_t> seed_dist_;
    std::vector<rng_t> thread_rng_vec_;
};

double timing(count_t num_runs) {
    
    MCIntegrator system(0.3, 0.4, 0.01, 91285);
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // start clock
    start = std::chrono::high_resolution_clock::now();
    system.measure_paths(num_runs);
    // end clock
    end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main(int argc, char* argv[]) {
    std::cout << timing(1e5) << std::endl;
    return 0;
}
