// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:54:31 CET
// File:    population.hpp

#ifndef __POPULATION_HEADER
#define __POPULATION_HEADER

#include <animal.hpp>
#include <list>
#include <utility>
#include <vector>
#include <random>
#include <functional> // COMMENT: missing include

namespace Penna {

template<class T>
class Population {
public:
    typedef Animal::age_type age_type;
    typedef unsigned int size_type; 
    typedef std::list<Animal> container_type;

    // constructors
    std::default_random_engine randgen;
    
    Population (size_type nmax = 10, size_type n = 0, T const & t = std::uniform_int_distribution<unsigned int>(0, 64)): nmax_(nmax), population_(container_type()), distr_(t){ /// distr needs to fulfill the property that distr(randgen) returns a value convertible to age_type (a.k.a. unsigned int)
        
        age_type m_previous = Genome::get_mutation_rate(); /// get previous mutation rate 
        Genome perfect_gene;
                
        for(size_type i = 0; i < n; ++i) {
            age_type rand_m = age_type(distr_(randgen));
            while(0 > rand_m or rand_m > Genome::number_of_genes ) {
                rand_m = age_type(distr_(randgen));
            }
            Genome::set_mutation_rate(rand_m); 
            population_.push_back(Animal(perfect_gene.mutate()));
        }
        
        Genome::set_mutation_rate(m_previous); ///restore mutation rate
        
    }
    
    // combines all the effects of one year on the population
    std::pair<size_type, size_type> add_year() {
        std::pair<size_type, size_type> values;
        values.first = reproduce();
        values.second = die();
        grow();
        return values;
    }

    void set_nmax(size_type n) {
        nmax_ = n;
    }
    
    // counts the number of animals in the population
    size_type size() const {
        return population_.size();
    } 
    
    age_type tot_age() const {
        age_type count = 0;
        for(auto it = population_.begin(); it != population_.end() ; ++it) {
            count += it -> age();
        }
        return count;
    }
    
    
private:
    // ages the whole population by one year
    void grow() {
        for(auto it = population_.begin(); it != population_.end() ; ++it) {
            it -> grow();
        }
    }
    
    // lets the mature animals generate offspring
    size_type reproduce() {
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
    size_type die(bool random_death_exists = 1) {
        
        size_type nbefore = population_.size();
        population_.remove_if(std::mem_fun_ref(&Animal::is_dead));
        if (random_death_exists)
        {
            population_.remove_if(random_death(nmax_, population_.size()));
        }
        
        return nbefore - population_.size();
    }

    size_type nmax_; /// maximum number of animals
    
    container_type population_; /// I choose lists because I never want to access only one Animal

    T distr_; /// random number distribution for the initial population
};

}

#endif //__POPULATION_HEADER

