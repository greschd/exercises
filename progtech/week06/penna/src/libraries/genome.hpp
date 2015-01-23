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
    using gene_t = bool;
    using length_t = int;

    genome_class();                     // Default constructor
    genome_class(genome_class const &);         // Copy constructor
    genome_class(genome_class const &, bool);   // Copy constructor with optional mutation
    
    void set(length_t k, gene_t b);
    
    bool read(length_ k);
    
    void mutate;
    
    void setgenomelength(length_t n);

private:
    static length_t const genomelength;
    std::vector<gene_t> genome;
    
};

#endif //__GENOME_HEADER
