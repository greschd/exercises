// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:18:49 CET
// File:    genome_test.cpp

#include <iostream>
#include "genome.hpp"

using namespace Penna;

void showgene(Genome g) {
        for(age_type i = 0; i < Genome::number_of_genes; ++i) {
        std::cout << not(g.is_bad(i));
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
    
    // Checking the default constructor
    Genome ref_genome;
    std::cout << "The default genome looks like this:" << std::endl;
    showgene(ref_genome);
    
    std::cout << "Flipping 20 genes (on average) looks like this:" << std::endl;
    Genome::set_mutation_rate(20);
    for(uint i = 0; i < 5; ++i) {
        Genome new_genome = ref_genome.mutate();
        showgene(new_genome);
    }
    
    // Checking the mutation function: 
    // Checking if mutation_rate_ = number_of_genes / 2 actually gives a probability of flipping of 1/2
    // This test uses all genome member functions (directly or implicitly)
    Genome::set_mutation_rate(Genome::number_of_genes / 2);
    uint reps = 1000;
    age_type count = 0;
    for(uint i = 0; i < reps; ++i) {
        Genome new_genome = ref_genome.mutate();
        count += new_genome.count_bad(Genome::number_of_genes);
    }
    std::cout << "In " << reps << " mutated genomes, the measured flipping rate is " << double(count) / (reps * Genome::number_of_genes) 
    << " when the mutation probability is set to 1/2 * number_of_genes" << std::endl << std::endl;
}

