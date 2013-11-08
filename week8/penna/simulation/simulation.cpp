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

void measurement(double m0, double m, size_type nmax, size_type n0, age_type T, age_type R, age_type years, std::string name) {
    
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
    std::string mname = "m_";
    mname.append(name).append(".txt");
    std::ofstream os;
    os.open(mname);
    os << "year population_size" << std::endl;
    for(uint i = 0; i < years; ++i) {
        os << i << " " << values.at(i) << std::endl;
    }
    os.close();
    
    std::string vname = "v_";
    vname.append(name).append(".txt");
    std::ofstream os2;
    os2.open(vname);
    os2 << "initial_mutation mutation_rate nmax n0 T R" << std::endl;
    os2 << m0 << " " << m << " " << nmax << " " << n0 << " " << T << " " << R << std::endl;
    os2.close();
}

int main(int argc, char* argv[]) {
    
    for(uint i = 0; i < 13; ++i) {
        measurement(0.5, 0.2 + 0.05*i, 10000, 100, 5, 10, 200, std::to_string(i + 1));
    }
    for(uint j = 0; j < 4; ++j) {
        measurement(0.5, 0.05 + 0.05*j, 10000, 100, 2, 10, 200, std::to_string(j + 13));
    }
}
