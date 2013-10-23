// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 16:55:20 CEST
// File:    genome.hpp

/*------------------------------*/
/*         genome_class         */
/*------------------------------*/
// Contains the genome of an animal (i.e. a boole vector of size = genomelength)

// MEMBER FUNCTIONS:

// constructor: default is a vector containing false, of size = genomelength
// copy constructor: copies a genome
// additional option "true" if new genome should be mutated, "false" else; mutating == flipping each bool 
// with probability = mrate (from environment_class)

// set(k, b): sets the k'th element (must be in (0, size of genome)) to b (b = true, false)
// read(k): reads the k'th element
// mutate: flips each element with probability mrate

// setgenomelength: sets the value of the static variable genomelength

#ifndef __GENOME_HEADER
#define __GENOME_HEADER

#include <environment.hpp>
#include <vector>

class genome_class {
public:

    genome_class();                     // Default constructor
    genome_class(genome_class);         // Copy constructor
    genome_class(genome_class,bool);    // Copy constructor with optional mutation
    
    void set(int k, bool b);
    
    bool read(int k);
    
    void mutate;
    
    void setgenomelength(int n);

private:
    static int const genomelength;
    std::vector<bool> genes;
    
};

#endif //__GENOME_HEADER
