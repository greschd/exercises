// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:17:02 CET
// File:    genome.cpp

#include "genome.hpp"
#include <chrono>
#include <random>
#include <iostream>

namespace Penna 
{
    void Genome::set_mutation_rate( Genome::age_type m ) {
        mutation_rate_ = m;
    }
    
    Genome::age_type Genome::get_mutation_rate() {
        return mutation_rate_;
    }
    
    // Default constructor: Initialize genes to all good. 
    Genome::Genome(): genes_(std::bitset<number_of_genes>()) {
        }
    // Copy constructor
    Genome::Genome(Genome const & gene): genes_(gene.genes_) {}
    
    // Check if i'th gene is bad. (index starts at 0)
    bool Genome::is_bad(Genome::age_type i) const {
        if(i >= number_of_genes) {
            return 0;
        }
        else {
            return genes_.test(i);
        }
    }
    
    // Count number of bad genes at age n. (index starts at 0)
    Genome::age_type Genome::count_bad( Genome::age_type n) const {
        /// counting through the first n elements of the genome (including 0)
        Genome::age_type count = 0;
        for(Genome::age_type j = 0; j < n + 1; ++j) {
            if( is_bad(j) )
                ++count;
        }
        return count;
    }
    
     // Generate a copy of this, except for M flipped genes.   
    Genome Genome::mutate(randgen_type & G) {
        /// setting up the random number generator (with a time - based seed)
        std::uniform_int_distribution<Genome::age_type> randnr(0, number_of_genes - 1);
        
        /// generating the new genome (no mutation yet)
        Genome newgenome(*this);
        
        /// flipping each bit with probability m / number_of_genes
        for(Genome::age_type i = 0; i < number_of_genes; ++i) {
            if(randnr(G) < mutation_rate_) {
                newgenome.genes_.flip(i);
            }
        }
        return newgenome;
    }
    
    Genome::age_type Genome::mutation_rate_ = 10;
}



