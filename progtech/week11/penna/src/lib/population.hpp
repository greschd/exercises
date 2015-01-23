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
#include <algorithm>

namespace Penna {

class Population {
public:
    typedef Animal::age_type age_type;
    typedef unsigned int size_type; 
    typedef std::list<Animal> container_type;
    typedef std::vector<size_type> measurement_container_type;
    typedef double average_type;
    typedef Genome::randgen_type randgen_type;

    // constructors
    
    Population(randgen_type & rng, size_type const & nmax = 10, size_type const & n = 5) : nmax_(nmax) { 
        
        age_type m_previous = Genome::get_mutation_rate(); /// get previous mutation rate 
        Genome perfect_gene;
        std::uniform_int_distribution<age_type> distr(0, Genome::number_of_genes);
                
        for(size_type i = 0; i < n; ++i) {
            age_type rand_m = age_type(distr(rng));
            while(0 > rand_m or rand_m > Genome::number_of_genes ) {
                rand_m = distr(rng);
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
    
    // counts the number of animals in the population
    size_type size() const {
        return population_.size();
    } 
    
    // get the distribution of bad genes
    measurement_container_type gene_distr() {
        measurement_container_type result(Genome::number_of_genes, 0);
        for(auto it = population_.begin(); it != population_.end(); ++it) {
            for(age_type i = 0; i < Genome::number_of_genes; ++i) {
                if (it -> get_genome().is_bad(i)) {
                    ++result.at(i);
                }
            }
        }
        return result;
    }
    
  protected:
    // function object to check for death of the animal
    class animal_dies {
    public:    
        typedef bool return_type;

        animal_dies(size_type const & N0, size_type const & N): N0_(N0), N_(N) {}

        return_type operator()(Animal const & A) {
            return ((rand() % N0_) < N_) || A.is_dead() ;
        }
    private:
        const size_type N0_;
        const size_type N_;
    };
    
    // ages the whole population by one year
    void grow() {
        std::for_each(population_.begin(), population_.end(), std::mem_fun_ref(&Animal::grow));
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
      
      //check out std::transform (i couldn't figure out how to do this whilst passing the argument G)
    }

    // kills dying animals 
    virtual void die() {
        size_type nbefore = population_.size();
        population_.remove_if(animal_dies(nmax_, nbefore));
    }
    
    average_type die_measure() {
        age_type ages = 0;
        size_type deaths = 0;
        size_type nbefore = population_.size();
        for(auto it = population_.begin(); it != population_.end();) {
            if((it -> is_dead()) or animal_dies(nmax_, nbefore)(*it)) {
                ages += it -> age();
                ++deaths;
                it = population_.erase(it); /// takes care of ++it
                //this will remove elements from population_!! (it's supposed to, so you can easily "turn on measurement" while still iterating through the years)
            }
            else {
                ++it;
            }
        }
        return ages/average_type(deaths);
    }
    
    

    size_type nmax_; /// maximum number of animals
    
    container_type population_; /// I choose lists because I never want to access only one Animal
  };

}

#endif //__POPULATION_HEADER

