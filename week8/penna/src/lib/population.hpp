// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:54:31 CET
// File:    population.hpp

#ifndef __POPULATION_HEADER
#define __POPULATION_HEADER

#include <animal.hpp>
#include <list>

namespace Penna {

class Population {
public:
    typedef unsigned int age_type;
    typedef uint size_type;
    typedef std::list<Animal> container_type;

    
    Population();
    Population(size_type = 0, age_type = Genome::get_mutation_rate()); // specify number of animals and initial rate of bad genes
    
    
    size_type const size(); // counts the number of animals in the population
    
    
    void grow(); // ages the whole population by one year
    
    void reproduce(); // lets the mature animals generate offspring
    
    bool test_dead(const Animal &); // checks if an animal is dead
    
    void die(); // kills dying animals 
    
    void add_year(); // combines all the effects of one year on the population
    
    static void set_nmax(size_type); 
    
private:
    container_type population_; /// I choose lists because I never want to access only one Animal
    
    static size_type nmax_; /// maximum number of animals
};

}

#endif //__POPULATION_HEADER

