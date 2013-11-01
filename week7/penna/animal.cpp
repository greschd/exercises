// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:16:39 CET
// File:    animal.cpp

#include <iostream>
#include "animal.hpp"

namespace Penna {
    
    void Animal::set_bad_threshold(age_type t) {
        Animal::bad_threshold_ = t;
    }
    
    void Animal::set_maturity_age( age_type r ) {
        Animal::maturity_age_ = r;
    }
    
    // Default constructor: Uses all good genome.
    Animal::Animal(): gen_(), age_(0) {}
    
    // Constructor using a given genome.
    Animal::Animal(Genome const & gen) : gen_(gen), age_(0) {}

    // I choose the first gene to be evaluated at age 0 (not 1)
    // and the Animal to die when the threshold is surpassed (not at the threshold)
    bool Animal::is_dead() const {  
        return (gen_.count_bad(age_) > bad_threshold_);
    }
    
    bool Animal::is_mature() const {
        return age_ > maturity_age_;
    }
    
    // Make the animal grow older by one year.
    void Animal::grow() {
        ++age_;
    }
    
    // Create a baby animal inheriting its genome from this except for some random mutations.
    Animal Animal::give_birth() const {
        Animal baby(gen_);
        baby.gen_.mutate();
        return baby;
    }
    
}
