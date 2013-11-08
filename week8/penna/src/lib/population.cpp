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
    Population::Population(size_type n, age_type m, bool flat_distribution): population_(container_type()) {
        /// get previous mutation rate and then change it to m
        age_type m_previous = Genome::get_mutation_rate();
        Genome perfect_gene;
        if(flat_distribution) {
            for(size_type i = 0; i < n; ++i) {
                Genome::set_mutation_rate(rand()%Genome::number_of_genes);
                population_.push_back(Animal(perfect_gene.mutate()));
            }
            
        }
        else {
            Genome::set_mutation_rate(m); 
            /// construct a perfect gene and mutate the new animal's gene from there
            for(size_type i = 0; i < n; ++i) {
                population_.push_back(Animal(perfect_gene.mutate()));
            }
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
    size_type Population::die(bool random_death_exists) {
        
        size_type nbefore = population_.size();
        population_.remove_if(std::mem_fun_ref(&Animal::is_dead));
        if (random_death_exists)
        {
            population_.remove_if(random_death(nmax_, nbefore));
        }
        
        return nbefore - population_.size();
    }
    
    // combines all the effects of one year on the population
    std::pair<size_type, size_type> Population::add_year() {
        std::pair<size_type, size_type> values;
        values.first = reproduce();
        values.second = die();
        grow();
        return values;
    }

    void Population::set_nmax(size_type n) {
        nmax_ = n;
    }
    
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
    
    std::vector<age_type> Population::bad_distribution() const {
        std::vector<age_type> distr(Genome::number_of_genes + 1);
        for(auto it = population_.begin(); it != population_.end(); ++it) {
            ++distr[it -> count_bad()];
        }
        return distr;
    }
    
    size_type Population::nmax_ = 10;
}
