// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:54:31 CET
// File:    population.hpp

#ifndef __POPULATION_HEADER
#define __POPULATION_HEADER

#include <animal.hpp>
#include <list>
#include <utility>
#include <vector>
#include <functional> // COMMENT: missing include

namespace Penna {

class Population {
public:
    typedef unsigned int age_type;
    typedef unsigned int size_type; // COMMENT: uint is not a standard type!
    typedef std::list<Animal> container_type;

    
    Population();
    Population(size_type = 0, age_type = Genome::get_mutation_rate(), bool = true); // specify number of animals and initial rate of bad genes (only used if flat distribution is turned off)
    
    // COMMENT: move to private, you do not want the user to mess up with the growing
    void grow(); // ages the whole population by one year
    
    // COMMENT: move to private, you do not want the user to mess up with the growing
    size_type reproduce(); // lets the mature animals generate offspring, returns number of births
    
    // COMMENT: move to private, you do not want the user to mess up with the growing
    size_type die(bool = true); // kills dying animals, returns number of deaths
    
    std::pair<size_type, size_type> add_year(); // combines all the effects of one year on the population, returns number of births and deaths as a pair.
    
    static void set_nmax(size_type); 
    
    size_type size() const ; // counts the number of animals in the population
    
    age_type tot_age() const; // counts up the age of the whole population
    
    std::vector<age_type> bad_distribution() const; // returns the distribution of the number of bad genes in the Animals
    
private:
    container_type population_; /// I choose lists because I never want to access only one Animal
    
    static size_type nmax_; /// maximum number of animals
};

}

#endif //__POPULATION_HEADER

