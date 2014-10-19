// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    18.10.2014 01:18:34 CEST
// File:    serial.cpp

#include <cmath>
#include <random>
#include <iostream>

typedef double res_t;
typedef int count_t;
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
                    counts_(),
                    rng_(seed),
                    dist_(0,1){}

    void measure_paths(count_t const & num_iter) {
        res_t xtemp(x_);
        res_t ytemp(y_);
        res_t a;
        count_t count;
        // heating up the RNG
        for(uint i = 0; i < 100; ++i) {
            dist_(rng_);
        }
        for(count_t i = 0; i < num_iter; ++i) {
            count = 0;
            // check if (xtemp, ytemp) is still in [0,1]^2
            while(0 < xtemp && xtemp < 1 && 0 < ytemp && ytemp < 1) {
                a = dist_(rng_);
                xtemp += d_ * std::cos(2. * pi * a);
                ytemp += d_ * std::sin(2. * pi * a);
                ++count;
            }
            // accumulate results in res_
            counts_.push_back(count);
            xtemp = x_;
            ytemp = y_;
        }
    }

    void print() const {
        for(auto c: counts_) {
            std::cout << c << ", ";
        }
    }
    
private:
    const res_t x_;
    const res_t y_;
    const res_t d_;
    std::vector<count_t> counts_;
    std::mt19937_64 rng_;
    std::uniform_real_distribution<res_t> dist_;
};

int main(int argc, char* argv[]) {
    count_t num_runs = 100000;
    MCIntegrator system(0.3, 0.4, 0.01, 91285);
    system.measure_paths(num_runs);
    system.print();
    num_runs *= 2;
    return 0;
}
