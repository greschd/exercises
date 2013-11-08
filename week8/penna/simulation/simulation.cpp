// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:51:11 CET
// File:    simulation.cpp

#include <iostream>
#include <fstream>
#include <population.hpp>
#include <vector>


typedef uint size_type;
typedef uint age_type;
using namespace Penna;

void measurement(double m0, double m, size_type nmax, size_type n0, age_type T, age_type R, age_type years, std::string output) {
    
    // setting up parameters
    Genome::set_mutation_rate(Genome::number_of_genes * m);
    Population::set_nmax(nmax);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
    
    Population labrats(n0, Genome::number_of_genes * m0);
    std::vector<size_type> values(years); 
    
    // iteration over the years
    for(uint i = 0; i < years; ++i) {
        labrats.add_year();
        values[i] = labrats.size();
    }
    
    // output
    std::ofstream os;
    os.open(output);
    os << "year population_size" << std::endl;
    
    for(uint i = 0; i < years; ++i) {
        os << i << " " << values.at(i) << std::endl;
    }
    os.close();
}

int main(int argc, char* argv[]) {
    
    measurement(0.5, 0.25, 10000, 100, 5, 11, 100, "measurement.txt");
}
