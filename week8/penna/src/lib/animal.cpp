// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:16:39 CET
// File:    animal.cpp

#include <iostream>
#include <animal.hpp>

namespace Penna {
    typedef unsigned int age_type;
    
    void Animal::set_bad_threshold(age_type t) {
        Animal::bad_threshold_ = t;
    }
    
    age_type Animal::bad_threshold_(0); // setting the threshold to 0 unless otherwise specified
    
    void Animal::set_maturity_age( age_type r ) {
        Animal::maturity_age_ = r;
    }
    
    age_type Animal::maturity_age_(0); // Setting R to 0 if nothing else is specified
    
    // Default constructor: Uses all good genome.
    Animal::Animal(): gen_(), age_(0) {}
    
    // Constructor using a given genome.
    Animal::Animal(Genome const & gen) : gen_(gen), age_(0) {}

    // I choose the first gene to be evaluated at age 0 (not 1)
    // and the Animal to die when the threshold is surpassed (not at the threshold)
    // or when it surpasses the maximum age (i.e. age = number_of_genes_)
    bool Animal::is_dead() const {  
        return (gen_.count_bad(age_) > bad_threshold_) || (age_ >= Genome::number_of_genes);
    }
    
    bool Animal::is_mature() const {
        return age_ > maturity_age_;
    }
    
    age_type Animal::age() const {
        return age_;
    }
    
    age_type Animal::count_bad(age_type a) const {
        return gen_.count_bad(a);
    }
    
    // Make the animal grow older by one year.
    void Animal::grow() {
        ++age_;
    }
    
    // Create a baby animal inheriting its genome from this except for some random mutations.
    Animal Animal::give_birth() const {
        Animal baby(gen_.mutate());
        return baby;
    }
}
