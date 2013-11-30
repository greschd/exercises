// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    27.11.2013 16:30:19 CET
// File:    fishing.hpp

#ifndef __FISHING_HEADER
#define __FISHING_HEADER

#include <population.hpp>

namespace Penna {

class Fishing: public Population {
public:
    typedef double p_type;
    typedef Population::age_type age_type;
    typedef Population::size_type size_type;
    typedef Population::randgen_type randgen_type;
    typedef Population::container_type container_type;
    
    // constructor
    Fishing(randgen_type & rng,const size_type  nmax = 10, const size_type n = 5, p_type const & p = 0, age_type const & a = 0): 
                Population(rng, nmax, n), f_probability_(p), min_age_(a) {}
                
    // set fishing probability
    void set_f_probability (p_type const & p) {
        f_probability_ = p;
    }
    
    // set minimum fishing age
    void set_min_age (age_type const & L) {
        min_age_ = L;
    }
    
    
private:
    // function object to check for death of the animal
    class animal_dies_fishing {
    public:    
        typedef bool return_type;

        animal_dies_fishing(size_type const & N0, size_type const & N, p_type const & p, age_type const & am): N0_(N0), N_(N), f_p_(p), a_min_(am){}

        return_type operator()(Animal const & A) const {
            return (((rand() % N0_) < N_) || A.is_dead() || fishing_death(A)) ;
        }
        
        // checks if the animal gets fished
        bool fishing_death(Animal const & A) const {
            return (A.age() >= a_min_) && (drand48() < f_p_);
        }
        
    private:
        const size_type N0_;
        const size_type N_;
        const p_type f_p_;
        const age_type a_min_;
    };
    
    // kill dead or fished animals
    void die () {
        size_type nbefore = population_.size();
        population_.remove_if(animal_dies_fishing(nmax_, nbefore, f_probability_, min_age_)); 
    }  
    
    p_type f_probability_;
    
    age_type min_age_;
    
};

}

#endif //__FISHING_HEADER

