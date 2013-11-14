// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:51:11 CET
// File:    simulation.cpp

#include <iostream>
#include <fstream>
#include <population.hpp>
#include <vector>


typedef unsigned int size_type;
typedef unsigned int age_type;
using namespace Penna;


template<class U>
Population<U> make_pop(size_type nmax = 10, size_type n = 0, U const & distr = std::uniform_int_distribution<age_type>(0, 64))
{
    return Population<U>(nmax, n, distr);
}

template<class U>
void measurement(size_type M, size_type nmax, size_type n0, age_type T, age_type R, age_type years, std::string name, U const & distr) {
    
    auto labrats = make_pop(nmax, n0, distr);
    Genome::set_mutation_rate(M);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
    
    age_type step = 1;
    std::vector<size_type> size_values(years);
    
    // iteration over the years
    for(age_type i = 0; i < years; ++i) {
        labrats.add_year();
        size_values[i] = labrats.size();
    }
    
    // output
    std::string mname = "m_";
    mname.append(name).append(".txt");
    std::ofstream os;
    os.open(mname);
    os << "year population_size" << std::endl;
    for(age_type i = 0; i < years; ++i) {
        os << i * step << " " << size_values.at(i) << std::endl;
    }
    os.close();
}
int main(int argc, char* argv[]) {
    
    
    size_type nmax(2000);
    size_type n0(1000);
    age_type years(100);
    
    std::normal_distribution<double> distr(0.4,0.05);
    
    // population size measurements
    measurement(0, nmax, n0, 2, 8, years, "0", distr);
    measurement(8, nmax, n0, 2, 8, years, "8", distr);
    
    return 0;
}
