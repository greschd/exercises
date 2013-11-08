// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:54:44 CET
// File:    population.cpp

#include <population.hpp>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

namespace Penna {
    typedef unsigned int age_type;
    typedef uint size_type;
    typedef std::list<Animal> container_type;
    
    // constructors
    Population::Population(): population_(container_type()){}
    Population::Population(size_type n, age_type m): population_(container_type()) {
        /// get previous mutation rate and then change it to m
        age_type m_previous = Genome::get_mutation_rate();
        Genome::set_mutation_rate(m); 
        /// construct a perfect gene and mutate the new animal's gene from there
        Genome perfect_gene;
        for(size_type i = 0; i < n; ++i) {
            population_.push_back(Animal(perfect_gene.mutate()));
        }
        Genome::set_mutation_rate(m_previous); ///restore mutation rate
    }
    
    // ages the whole population by one year
    void Population::grow() {
        for(auto it = population_.begin(); it != population_.end() ; ++it) {
            it -> grow();
        }
    }
    
    // lets the mature animals generate offspring
    size_type Population::reproduce() {
        container_type babies;
        for(auto it = population_.begin(); it != population_.end(); ++it) {
            if(it -> is_mature()) {
                babies.push_back(it -> give_birth());
            }
        }
        size_type birth_nr = babies.size();
        population_.splice(population_.end(), babies);
        return birth_nr;
    }
        
    // function object to check for random death
    class random_death {
    public:    
        typedef size_type argument_type;
        typedef bool return_type;
    
        random_death(argument_type const & N0, argument_type const & N): N0_(N0), N_(N) {}
    
        return_type operator()(Animal const & A) {
            return (rand() % N0_) < N_;
        }
    private:
        size_type N0_;
        size_type N_;
    };

    // kills dying animals 
    size_type Population::die() {
        size_type nbefore = population_.size();
        population_.remove_if(std::mem_fun_ref(&Animal::is_dead));
        population_.remove_if(random_death(nmax_, nbefore));
        return nbefore - population_.size();
    }
    
    // combines all the effects of one year on the population
    void Population::add_year() {
        reproduce();
        die();
        grow();
    }

    void Population::set_nmax(size_type n) {
        nmax_ = n;
    }
    
    // measurement functions
    
    // counts the number of animals in the population
    size_type Population::size() const {
        return population_.size();
    } 
    
    age_type Population::tot_age() const {
        age_type count = 0;
        for(auto it = population_.begin(); it != population_.end() ; ++it) {
            count += it -> age();
        }
        return count;
    }
    
    size_type Population::nmax_ = 10;
}
