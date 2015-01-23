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

void setup(double m, size_type nmax, age_type T, age_type R) {     // setting up parameters
    Genome::set_mutation_rate(Genome::number_of_genes * m);
    Population::set_nmax(nmax);
    Animal::set_bad_threshold(T);
    Animal::set_maturity_age(R);
}

void measurement(double m0, double m, size_type nmax, size_type n0, age_type T, age_type R, age_type years, std::string name) {
    
    setup(m, nmax, T, R);
    Population labrats(n0, Genome::number_of_genes * m0);
    std::vector<size_type> size_values(years); 
    
    // iteration over the years
    for(uint i = 0; i < years; ++i) {
        labrats.add_year();
        size_values[i] = labrats.size();
    }
    
    // output
    std::string mname = "m_";
    mname.append(name).append(".txt");
    std::ofstream os;
    os.open(mname);
    os << "year population_size" << std::endl;
    for(uint i = 0; i < years; ++i) {
        os << i << " " << size_values.at(i) << std::endl;
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

double avg_age_of_death(double m0, double m, size_type nmax, size_type n0, age_type T, age_type R, age_type years) {
    
    setup(m, nmax, T, R);

    Population labrats(n0, Genome::number_of_genes * m0);
    std::vector<size_type> size_values(years); 
    std::vector<size_type> death_values(years); 
    
    // iteration over the years
    for(uint i = 0; i < years; ++i) {
        std::pair<size_type, size_type> p = labrats.add_year();
        size_values[i] = labrats.size();
        death_values[i] = p.second;
    }
    
    size_type dyingage_sum = 0;
    size_type deaths_sum = 0;
    for(uint i = 0; i < years; ++i) {
        dyingage_sum += size_values[i];
        deaths_sum += death_values[i];
    }
    dyingage_sum -= labrats.tot_age(); /// the summed age of death is equal to the summed population sizes minus the total age of the population at the end
    
    return double(dyingage_sum)/deaths_sum;
}

void gene_distribution(double m0, double m, size_type nmax, size_type n0, age_type T, age_type R, age_type years) {
    
    setup(m, nmax, T, R);
    Population labrats(n0, Genome::number_of_genes * m0);
    Population reference = labrats;
    for(age_type i = 0; i < years; ++i) {
        labrats.add_year();
    }
    
    std::vector<size_type> initial_state = reference.bad_distribution();
    std::vector<size_type> final_state = labrats.bad_distribution();
    
    std::ofstream os;
    os.open("initial.txt");
    os << "threshold survivors" << std::endl;
    for(uint i = 0; i <= Genome::number_of_genes; ++i) {
        os << i << " " << initial_state.at(i) << std::endl;
    }
    os.close();
    
    std::ofstream os2;
    os2.open("final.txt");
    os2 << "threshold survivors" << std::endl;
    for(uint i = 0; i < Genome::number_of_genes; ++i) {
        os2 << i << " " << final_state.at(i) << std::endl;
    }
    os2.close();
    
}


int main(int argc, char* argv[]) {
    size_type nmax(10000);
    size_type n0(100);
    age_type years(200);
    
    // population size measurements
    for(uint i = 0; i < 13; ++i) {
        measurement(0.5, 0.2 + 0.05*i, nmax, n0, 5, 10, years, std::to_string(i + 1));
    }
    for(uint j = 0; j < 8; ++j) {
        measurement(0.5, 0.05 + 0.05*j, nmax, n0, 3, 10, years, std::to_string(j + 13));
    }
    
    // average age of death measurements
    uint n(50);
    double step(0.02);
    std::vector<double> averages(n);
    for(uint i = 0; i < n; ++i) {
        averages[i] = (avg_age_of_death(0.5, step * i, nmax, n0, 5, 10, years));
    }
    /// output
    std::ofstream os;
    os.open("age_of_death.txt");
    os << "mutation_rate avg_age_of_death" << std::endl;
    for(uint i = 0; i < n; ++i) {
        os << step*i << " " << averages[i] << std::endl;
    }
    os.close();
    
    gene_distribution(0.5, 0.05, nmax, n0, 15, 60, 100 * years); /// I increase R to get rid of bad genes in the "later" years
    
}
