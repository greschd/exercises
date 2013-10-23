// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 16:55:17 CEST
// File:    animal.hpp

//*-----------------------------*/
/*        animal_class          */
/*------------------------------*/
// Contains the relevant information about an animal, i.e. age (type uint), state of sickness (type uint)
// (how many negative genes it has had in its lifetime) and the genome (type genome). 
// If T denotes the number of years passed in the simulation, an animal will have age T+1 (or 1) if born in the last year 
// and T+2 if born in the current year. 

// MEMBER FUNCTIONS:

// constructor: default values are age = year + 2, sickness = 0, genome with default genome value (all false). 
// input can be an initial age (to be set to T+2), a parent (from whom the genome will be copied) and a mutation rate (double m)
// (to generate mutations in the copying of the genome)

// setage(n): set the age of the animal to n
// readage(): reads the age of the animal
// older(): increments the age of the animal by one and updates the state of sickness (+1 if the corresponding gene is true)

// readsick(): reads the state of sickness
// sicken: increments the state of sickness by 1

// readgene(): reads the genome of the animal

#ifndef __ANIMAL_HEADER
#define __ANIMAL_HEADER

#include <environment.hpp>
#include <genome.hpp>

class animal_class {

public:
    friend environment_class
    
    animal_class : age(int = environment_class::year + 2), sick(int = 0), gene(genome_class = genome_class(std));
    
    void setage(int);
    
    int readage();
    
    void older();
    
    int readsick();
    
    void sicken();
    
    genome_class readgene();
    
private:
    int age;
    int sick;
    genome_class gene;
};

#endif //__ANIMAL_HEADER
