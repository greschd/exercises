// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:17:02 CET
// File:    genome.cpp

#include "genome.hpp"
#include <chrono>
#include <random>

namespace Penna 
{
    void Genome::set_mutation_rate( age_type m ) {
        mutation_rate_ = m;
    }
    
    // Default constructor: Initialize genes to all good. 
    Genome::Genome(): genes_(std::bitset<number_of_genes>()) {
        }
    // Copy constructor
    Genome::Genome(Genome const & gene): genes_(gene.genes_) {}
    
    // Check if i'th gene is bad. (index starts at 0)
    bool Genome::is_bad(age_type i) const {
        return genes_.test(i);
    }
    
    // Count number of bad genes in first n years. (index starts at 0)
    age_type Genome::count_bad( age_type n) const {
        /// counting through the first n elements of the genome (including 0)
        age_type count = 0;
        for(age_type j = 0; j < n; ++j) {
            if( is_bad(j) )
                ++count;
        }
        return count;
    }
    
     // Generate a copy of this, except for M flipped genes.   
    Genome Genome::mutate() const {
        /// setting up the random number generator (with a time - based seed)
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // are we supposed to use our own random number generator?
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<age_type> randnr(0, number_of_genes-1);
        
        /// generating the new genome (no mutation yet)
        Genome newgenome(*this);
        
        /// flipping each bit with probability m / number_of_genes
        for(age_type i = 0; i < number_of_genes; ++i) {
            if(randnr(generator) < mutation_rate_)
                newgenome.genes_.flip(i);
        }
        
        return newgenome;
    }
    
    age_type Genome::mutation_rate_ = 0;

}

