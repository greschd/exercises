// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:51:11 CET
// File:    simulation.cpp

#include <iostream>
#include <population.hpp>

using namespace Penna;
int main(int argc, char* argv[]) {
    Genome::set_mutation_rate(Genome::number_of_genes / 4);
    Population::set_nmax(10000);
    Animal::set_bad_threshold(5);
    Animal::set_maturity_age(9);
    
    Population labrats(100, Genome::number_of_genes / 1.5);
    for(uint i = 0; i < 100; ++i) {
        labrats.add_year();
        std::cout << labrats.size() << "\n";
    }
    std::cout << std::endl;
    return 0;
}
