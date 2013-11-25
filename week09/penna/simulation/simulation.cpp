// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    07.11.2013 00:51:11 CET
// File:    simulation.cpp

#include <iostream>
#include <fstream>
#include <population.hpp>
#include <vector>

using namespace Penna;

typedef unsigned int size_type;
typedef unsigned int age_type;
typedef double average_type; 
typedef std::pair<average_type, size_type> age_size_pair;
typedef Genome::randgen_type randgen_type;

randgen_type rng;

// setting up some variables (that are the same for all measurements)
namespace var { 
    size_type nmax(10000);
    size_type n0(9000);
    age_type years(2000);
}

// workaround for not having to type the template argument manually
template<class U>
Population<U> make_pop(U const & distr)
{
    return Population<U>(distr, rng, var::nmax, var::n0);
}

// setting up the parameters
template<class U>
Population<U> setup(size_type M, age_type T, age_type R, U const & distr) {
    Genome::set_mutation_rate(M);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
    return make_pop(distr);
}

// measuring the size of the population each year
template<class U>
void measure_size(size_type M, age_type T, age_type R, std::string name, U const & distr) {
    
    auto pop = setup(M, T, R, distr);
    std::vector<size_type> size_values(var::years);
    
    // iteration over the years
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
        size_values[i] = pop.size();
    }
    
    // output
    std::string mname = "m_";
    mname.append(name).append(".txt");
    std::ofstream os;
    os.open(mname);
    os << "year population_size" << std::endl;
    for(age_type i = 0; i < var::years; ++i) {
        os << i  << " " << size_values.at(i) << std::endl;
    }
    os.close();
}

// sampling the average age at death and population size after the population has lived 'years'. 
template<class U>
age_size_pair sample_age_size(size_type M, age_type T, age_type R,  U const & distr) {
    auto pop = setup(M, T, R, distr);
    Genome::set_mutation_rate(M);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
    }
    age_size_pair results = std::make_pair(pop.add_year_measure(rng), pop.size());
    return results;
}

// calling the sampling function for different R (as in Penna's paper) and output
template<class U>
void measure_age_size(size_type M, age_type T, U const & distr) {
    age_type max_R = 16;
    std::vector<age_size_pair> results(0);
    for(age_type R = 0; R < max_R; ++R) {
        results.push_back(sample_age_size(M, T, R, distr));
    }
    // output
    std::ofstream os;
    os.open("m_ageatdeath.txt");
    os << "R avg_age_at_death population_size" << std::endl;
    for(age_type R = 0; R < max_R; ++R) {
        os << R  << " " << results.at(R).first << " " << results.at(R).second << std::endl;
    }
    os.close();
}

// measuring the distribution of bad genes in the final steady-state (after 'years')
template<class U>
void measure_genedistr(size_type M, age_type T, age_type R, U const & distr) {
    auto pop = setup(M, T, R, distr);
    for(age_type i = 0; i < var::years; ++i) {
        pop.add_year(rng);
    }
    std::vector<size_type> bad_gene_count = pop.gene_distr();
    
    // output
    std::ofstream os;
    os.open("m_genedistr.txt");
    os << "i bad_genes_at_i" << std::endl;
    for(age_type i = 0; i < Genome::number_of_genes; ++i) {
        os << i  << " " << bad_gene_count.at(i) << std::endl;
    }
    os.close();
}


int main(int argc, char* argv[]) {
    
    std::string str;
    std::cout << "enter a seed: ";
    std::getline(std::cin,str);
    std::seed_seq seed1 (str.begin(),str.end());
    rng.seed(seed1);
    
    std::uniform_int_distribution<unsigned int> distr1(0, Genome::number_of_genes);
    //~ std::normal_distribution<double> distr2(32, 10);
    
    // population size measurements
    measure_size(0, 2, 8, "0", distr1);
    measure_size(8, 2, 8, "8", distr1);
    std::cout << "finished 1st measurement" << std::endl;
    
    // measuring the age at death and population size 
    measure_age_size(2, 4, distr1);
    std::cout << "finished 2nd measurement" << std::endl;
    
    // measuring the gene distribution in steady - state
    measure_genedistr(8, 2, 8, distr1);
    std::cout << "finished 3rd measurement" << std::endl;
    
    return 0;
}
