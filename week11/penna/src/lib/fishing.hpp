// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    27.11.2013 16:30:19 CET
// File:    fishing.hpp

#ifndef __FISHING_HEADER
#define __FISHING_HEADER

#include <population.hpp>

namespace Penna {

class fishing: public population {
public:
    typedef double p_type;
    
    // set fishing probability
    void set_f_probability (p_type const & p) {
        f_probability_ = p;
    }
    
    // set minimum fishing age
    void set_min_age (age_type const & L) {
        min_age_ = L;
    }
    
    // checks if the animal gets fished
    bool fishing_death(Animal const & A) {
        return (A.age() >= min_age_) && (drand48() < f_probability_);
    }
    
    void die (bool random_death_exists = 1) {
        size_type nbefore = population_.size();
        population_.remove_if(std::mem_fun_ref(&Animal::is_dead)); //you can put this into the random_death predicate
        if (random_death_exists) {
            population_.remove_if(random_death(nmax_, nbefore));
        }
        population_.remove_if(fishing_death());
    } 
private:
    p_type f_probability_;
    age_type min_age_;
    
};

}

#endif //__FISHING_HEADER

