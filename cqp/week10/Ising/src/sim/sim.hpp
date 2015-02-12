// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    26.03.2014 20:46:58 CET
// File:    sim.hpp

#ifndef __BASELINE_GRESCHD_SIM_HEADER
#define __BASELINE_GRESCHD_SIM_HEADER

#include <types.hpp>
#include <global.hpp>

#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>

namespace mc_potts {
    
    struct sim {
        
        template< int L1
                , int L2
                , template<typename> class RNG
                , class GRID
                , class MATRIX>
        class impl {
            //---------------------local typedefs---------------------------//
            typedef int dir_t;
            typedef std::vector<double> resvec_t;
            
        public:
            impl(   double const & T_init,
                    double const & Jx,
                    double const & Jy,
                    uint32_t const & N_therm, 
                    uint32_t const & N_update = L1*L2):  
                        N_therm_(N_therm), 
                        N_update_(N_update), 
                        T_(T_init), 
                        Jx_(Jx),
                        Jy_(Jy),
                        system_(), 
                        energy_res_(0),
                        magn_res_(0) {
                clear();
            }
            
            
            // N_therm_ single spin updates
            void thermalize() {
                for(index_type i = 0; i < N_therm_; ++i) {
                    update();
                }   
            }
            
            // N_update_ single spin updates
            void update() {
                for(index_type i = 0; i < N_update_; ++i) {
                    update_spin_();
                }
            }
            
            //
            void measure() {
                energy_res_.push_back(energy_density_());
                magn_res_.push_back(magn_density_());
            }
            
            result_struct energy() const {
                return get_res_(energy_res_);
            }
            
            result_struct magn() const {
                return get_res_(magn_res_);
            }
            
            void set_T(double const & T) {
                clear_res_();
                T_ = T;
            }
            
            void clear() {
                RNG<spin_ret_type> spin_rng(0, S);
                
                // set all spins to a random state
                for(index_type i = 0; i < L1; ++i) {
                    for(index_type j = 0; j < L2; ++j) {
                        system_.set(i, j, spin_rng());
                    }
                }
            }
            
            uint8_t get(  uint32_t const & l1, uint32_t const & l2) const {
                return system_.get(l1, l2); 
            }
            
            void print() {
                for(index_type i = 0; i < L1; ++i) {
                    for(index_type j = 0; j < L2; ++j) {
                        std::cout << int(system_.get(i, j));
                    }
                    std::cout << std::endl;
                }
            }
        
        private:
        
    //------------------------observables-------------------------------//
        
            double magn_density_() const {
                spin_ret_type res = 0;
                for(index_type i = 0; i < L1; ++i) {
                    for(index_type j = 0; j < L2; ++j) {
                        res += system_.get(i, j);
                    }
                }
                return res / double(L1 * L2) - (S - 1) / 2.;
            }
            
            double energy_density_() const {
                double res = 0;
                for(index_type i = 0; i < L1; ++i) {
                    for(index_type j = 0; j < L2; ++j) {
                            res -= (system_.get(i, j) - (S - 1) / 2.) * (Jx_ * (system_.get_xnn(i, j) - (S - 1)) + Jy_ * (system_.get_ynn(i, j) - (S - 1)));
                    }
                }
                return res / (2. * L1 * L2);
            }
            
        //------------------------calculating the results from a vector-----//
            result_struct get_res_(resvec_t const & v) const {
                result_struct res;
                res.n = v.size();
                
                res.mean = std::accumulate(v.begin(), v.end(), 0.) / res.n;
                
                res.dev = 0;
                std::for_each(v.begin(), v.end(), [&](double x){res.dev += (x - res.mean)*(x - res.mean);});
                res.dev = sqrtf(res.dev / res.n);
                
                res.err = res.dev / sqrt(res.n);
                
                return res;
            }
        
            
        //------------------------single-spin update------------------------//
            void update_spin_() {
                
                RNG<index_type> rng1(0, L1);
                RNG<index_type> rng2(0, L2);
                RNG<dir_t> rngdir;
                RNG<double> rngprob;
                
                index_type i = rng1();
                index_type j = rng2();
                
                // choosing direction of the spin change
                dir_t dir = rngdir();
                dir = dir * 2 - 1;
                spin_ret_type temp = system_.get(i, j) + dir;
                
                //return if the new state isn't a valid state
                if(temp >= S or temp < 0) {
                    return;
                }
                
                // acceptance step
                double p = exp(dir / T_ *((Jx_ * (system_.get_xnn(i, j) - (S - 1))) + (Jy_ * system_.get_ynn(i, j) - (S - 1))));
                // S - 1: changing from representation as 0, 1 to physical spins (2 neighbours -> 2 * 1/2)
                double r = rngprob();
                if(p > r) {
                    system_.set(i, j, temp);
                }
            }
            
        //---------------------------clear results--------------------------//
            void clear_res_() {
                energy_res_ = resvec_t(0);
                magn_res_ = resvec_t(0);
            }
            
            
        //---------------------------private variables----------------------//
            
            // num_runs
            uint32_t N_therm_;
            uint32_t N_update_;
            
            // temperature
            double T_;
            double Jx_;
            double Jy_;
            
            // system
            typename GRID::template impl<L1, L2, MATRIX> system_;
            
            // results
            resvec_t energy_res_;
            resvec_t magn_res_;
            
        }; // impl
    }; // struct baseline_greschd_sim
    
} // namespace mc_potts


#endif //__BASELINE_GRESCHD_SIM_HEADER
