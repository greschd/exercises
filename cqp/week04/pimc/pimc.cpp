// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    13.03.2014 08:42:27 CET
// File:    pimc.cpp

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <math.h>
#include <fstream>
#include <iomanip>

typedef double val_t;
typedef int int_t;
typedef std::vector<val_t> conf_t;
typedef std::function<val_t(val_t const &)> func_t;
typedef std::mt19937 rng_t;
typedef std::uniform_real_distribution<val_t> posdist_t;
typedef std::uniform_int_distribution<int_t> dimdist_t;
typedef std::vector<int_t> rho_t;

#ifndef SEED
#define SEED 42
#endif

rng_t rng(SEED);
posdist_t rndnr1(-1., 1.);
posdist_t rndnr2(0, 1.);


class config_cl {
public:
    config_cl(val_t beta, int_t const & M, func_t const & V, val_t const & t): beta_(beta), M_(M), conf_(conf_t(M)), 
    V_(V), t_(t), rndnr_M_(dimdist_t(0, M - 1)), tau_(beta/(val_t(M))) {};
    
    val_t pot() const {
        val_t res = 0;
        auto acc = [&](val_t const & x){res += V_(x);};
        std::for_each(conf_.begin(), conf_.end(), acc);
        return res / M_;
    }
    
    val_t kin() const {
        val_t res = 0;
        for(int_t i = 0; i < M_; ++i) {
            res += (conf_.at(i) - conf_.at((i + 1) % M_))*(conf_.at(i) - conf_.at((i + 1) % M_));
        }
        // this isn't quite right...
        return 1 / (2. * tau_) - res / (2. * M_ * tau_ * tau_);
    }
    
    rho_t rho(val_t const & minpos, val_t const & maxpos, int_t const & sections) {
        rho_t res(sections);
        val_t range = maxpos - minpos;
        std::cout << range << std::endl;
        auto acc = [&](val_t const & x) {
            int_t n = int_t((x - minpos) * (sections) / range );
                if(n >= 0 && n < sections)
                    ++res.at(int_t((x - minpos) * (sections) / range ));
            };
        std::for_each(conf_.begin(), conf_.end(), acc);
        return res;
    }
    
    // sweep_nr = nr of accepted steps
    void update(int_t const & sweep_nr) {
        int_t i = 0;
        int_t acc = 0;
        for(;i < sweep_nr;) {
            if(step(t_)) 
                ++i;
            ++acc;
        }
    }
    
    val_t update_get_rate(int_t const & sweep_nr) {
        int_t i = 0;
        int_t acc = 0;
        for(;i < sweep_nr;) {
            if(step(t_)) 
                ++i;
            ++acc;
        }
        return val_t(i) / val_t(acc);
    }
    
private:
    
    bool step(val_t const & t) {
        int_t m = rndnr_M_(rng);
        val_t d = rndnr1(rng);
        val_t r = rndnr2(rng);
        val_t x = conf_.at(m);
        val_t temp = x + d * t;
        val_t rplus, rminus;
        rplus = conf_.at((m + 1) % M_);
        rminus = conf_.at((m + M_ - 1) % M_);
        val_t chi = exp(- ((rminus - temp)*(rminus - temp) + (rplus - temp)*(rplus - temp)) / (2. * tau_)) / exp(-((rminus - x)*(rminus - x) + (rplus - x)*(rplus - x)) /(2. * tau_)) * exp(- tau_ * (V_(temp) - V_(x)));
        // return true if the step is accepted
        if(chi > r) {
            conf_.at(m) = temp;
            return true;
        }
        // return false if the step isn't accepted    
        else return false;
    }
    
    const val_t beta_;
    const int_t M_;
    conf_t conf_;
    const func_t V_;
    const val_t t_;
    dimdist_t rndnr_M_;
    const val_t tau_;
};

int main(int argc, char* argv[]) {
    // enter values //
    val_t beta = 10;
    int_t M = 100;
    auto V = [&](val_t const & x){return x * x;};
    val_t t = 0.2;
    //--------------//
    
    // enter number of repetitions //
    int_t N = 512;
    int_t sweeps = 2000;
    //-----------------------------//
    
    //~ std::vector<std::vector<val_t>> res(N, std::vector<val_t>(2));
    
    config_cl conf(beta, M, V, t);
    //~ for(int_t i = 0; i < N; ++i) {
        //~ conf.update(sweeps);
        //~ res.at(i) = std::vector<val_t>({conf.pot(), conf.kin()});
    //~ }
    //~ 
    //~ std::ofstream write;
    //~ write.open("data.txt");
    //~ for(int_t i = 0; i < N; ++i) {
        //~ write << res.at(i).at(0) << " " << res.at(i).at(1) << std::endl;
    //~ }
    //~ write.close();
    
    for(uint i = 0; i < int(1e10); ++i) {
        conf.update(sweeps);
        std::cout << std::setprecision(4) << "Ekin: \t" << conf.kin() << "\tEpot: \t" << conf.pot() << std::endl;
    }
    
    return 0;
}



// it actually seems that an "approval rate" of about 0.5 is already "dangerous" because it leads to very slowly changing energies (drift).
