// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:51:11 CET
// File:    simulation.cpp

#include <iostream>
#include <fstream>
#include <fishing.hpp>
#include <vector>

using namespace Penna;

typedef unsigned int size_type;
typedef unsigned int age_type;
typedef double average_type; 
typedef std::pair<average_type, size_type> age_size_pair;
typedef Genome::randgen_type randgen_type;
typedef Fishing::p_type p_type;

randgen_type rng;

// setting up some variables (that are the same for all measurements)
namespace var { 
    size_type nmax(10000);
    size_type n0(9000);
    age_type years(500);
    p_type p1(0.075);
    p_type p2(0.085);  
    p_type p3(0.40); // you can fish out up to 40% of the adult population (that has already had the chance to reproduce) without destroying the population!
}

// setting up the parameters
Fishing setup(size_type M, age_type T, age_type R) {
    Genome::set_mutation_rate(M);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
    return Fishing(rng, var::nmax, var::n0);
}

// measuring the size of the population each year
void measure_size(size_type M, age_type T, age_type R, age_type a_min, std::string name) {
    
    auto pop = setup(M, T, R);
    std::vector<size_type> size_values;
    pop.set_min_age(a_min);
    
    // iteration over the years
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
        size_values.push_back(pop.size());
    }
    
    // first fishing parameter
    pop.set_f_probability(var::p1);
    // iteration over the years
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
        size_values.push_back(pop.size());
    }
    
    // second fishing parameter
    pop.set_f_probability(var::p2);
    // iteration over the years
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
        size_values.push_back(pop.size());
    }
    
    // third fishing parameter
    pop.set_f_probability(var::p3);
    // iteration over the years
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
        size_values.push_back(pop.size());
    }
    
    // output
    std::string mname = "size_";
    mname.append(name).append(".txt");
    std::ofstream os;
    os.open(mname);
    os << "year population_size" << std::endl;
    age_type N = size_values.size();
    for(age_type i = 0; i < N; ++i) {
        os << i  << " " << size_values.at(i) << std::endl;
    }
    os.close();
}



int main(int argc, char* argv[]) {
    
    std::string str = "10953ads86";
    std::seed_seq seed1 (str.begin(),str.end());
    rng.seed(seed1);
    
    
    // population size measurements
    measure_size(8, 2, 8, 0, "0");
    measure_size(8, 2, 8, 9, "9"); // minimal age for fishing = reproduction age 
    std::cout << "finished  measurement" << std::endl;
    

    
    return 0;
}
