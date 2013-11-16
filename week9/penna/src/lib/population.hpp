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
#include <functional> 

namespace Penna {

template<class T>
class Population {
public:
    typedef Animal::age_type age_type;
    typedef unsigned int size_type; 
    typedef std::list<Animal> container_type;
    typedef std::vector<size_type> measurement_container_type;
    typedef double average_type;
    typedef Genome::randgen_type randgen_type;

    // constructors
    
    Population (T const & t , randgen_type & rng, size_type nmax = 10, size_type n = 0): nmax_(nmax), population_(container_type()), distr_(t){ /// distr needs to fulfill the property that distr(randgen) returns a value convertible to age_type (a.k.a. unsigned int)
        
        age_type m_previous = Genome::get_mutation_rate(); /// get previous mutation rate 
        Genome perfect_gene;
                
        for(size_type i = 0; i < n; ++i) {
            age_type rand_m = age_type(distr_(rng));
            while(0 > rand_m or rand_m > Genome::number_of_genes ) {
                rand_m = distr_(rng);
            }
            Genome::set_mutation_rate(rand_m); 
            population_.push_back(Animal(perfect_gene.mutate(rng)));
        }
        
        Genome::set_mutation_rate(m_previous); ///restore mutation rate
        
    }
    
    // combines all the effects of one year on the population
    void add_year(randgen_type & G) {
        reproduce(G);
        die();
        grow();
    }
    
    // adding a year whilst measuring the ages of the dying animals
    average_type add_year_measure(randgen_type & G) {
        reproduce(G);
        average_type dyingage = die_measure();
        grow();
        return dyingage;
    }

    void set_nmax(size_type n) {
        nmax_ = n;
    }
    
    // counts the number of animals in the population
    size_type size() const {
        return population_.size();
    } 
    
    // get the distribution of bad genes
    measurement_container_type gene_distr() {
        measurement_container_type result(Genome::number_of_genes, 0);
        for(auto it = population_.begin(); it != population_.end(); ++it) {
            for(age_type i = 0; i < Genome::number_of_genes; ++i) {
                if (it -> get_genome().is_bad(i))
                {
                    ++result.at(i);
                }
            }
        }
        return result;
    }
    
private:
    // ages the whole population by one year
    void grow() {
        for(auto it = population_.begin(); it != population_.end() ; ++it) {
            it -> grow();
        }
    }
    
    // lets the mature animals generate offspring
    void reproduce(randgen_type & G) {
        container_type babies;
        for(auto it = population_.begin(); it != population_.end(); ++it) {
            if(it -> is_mature()) {
                babies.push_back(it -> give_birth(G));
            }
        }
        population_.splice(population_.end(), babies);
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
    void die(bool random_death_exists = 1) {
        size_type nbefore = population_.size();
        population_.remove_if(std::mem_fun_ref(&Animal::is_dead));
        if (random_death_exists)
        {
            population_.remove_if(random_death(nmax_, nbefore));
        }
        
    }
    
    average_type die_measure(bool random_death_exists = 1) {
        age_type ages = 0;
        size_type deaths = 0;
        size_type nbefore = population_.size();
        for(auto it = population_.begin(); it != population_.end();) {
            if((it -> is_dead()) or random_death(nmax_, nbefore)(*it)) {
                ages += it -> age();
                ++deaths;
                it = population_.erase(it); /// takes care of ++it
            }
            else {
                ++it;
            }
        }
        return ages/average_type(deaths);
    }
    
    

    size_type nmax_; /// maximum number of animals
    
    container_type population_; /// I choose lists because I never want to access only one Animal

    T distr_; /// random number distribution for the initial population
};

}

#endif //__POPULATION_HEADER

