// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    30.10.2013 13:18:29 CET
// File:    animal_test.cpp

#include <iostream>
#include <animal.hpp>

using namespace Penna;

// calculates the rate of animals that die because of genome defects (during their lifetime) 
// when born as a child of a healthy (perfect genome) parent with threshold t and mutation rate m
double dyingrate(age_type const & m, age_type const & t, uint N) {
    Genome::set_mutation_rate(m);
    Animal::set_bad_threshold(t);
    uint count = 0;
    for(uint i = 0; i < N; ++i) {
        Animal labrat3;
        Animal labrat4 = labrat3.give_birth();
        for(age_type j = 0; j < Genome::number_of_genes - 1; ++j) {
            labrat4.grow();
        }
        if(labrat4.is_dead()) {
            ++count;
        }
    }
    return double(count) / N;
}

void testdyingrate(age_type const & m, age_type const & t, uint N) {
    std::cout << "With mutation_rate = " << m << " and bad_threshold = " << t << ", r = " << dyingrate(m,t,N) << " of all the animals died. (" << N << " tested)" << std::endl;
}

int main(int argc, char* argv[]) {
    Animal labrat;
    
    // Checking if .grow(), is_mature() and set_maturity_age work as desired
    bool error = false;
    for(age_type i = 0; i < Genome::number_of_genes; ++i) {
        Animal::set_maturity_age(i+1);
        if(labrat.is_mature()) {
            error = true;
        }
        labrat.grow();
        if(labrat.is_mature()) {
            error = true;
        }
    }
    
    if(error) {
        std::cout << "an error occured" << std::endl;
    }
    else {
        std::cout << "Checked .grow(), is_mature and set_maturity_age without error." << std::endl << std::endl;
    }
    error = false;
    
    // Checking if the animal dies at age number_of_genes
    if(labrat.is_dead()){
        std::cout << "Old animals die as desired." << std::endl << std::endl;
    }
    else {
        std::cout << "Old animals do not die, please check your code." << std::endl << std::endl;
    }
        
    // Checking if the default animal has all good genes. (Threshold still at 0).
    Animal labrat2;
    for(age_type i = 0; i < Genome::number_of_genes - 1; ++i) {
        labrat2.grow();
    }
    if(labrat2.is_dead()){
        std::cout << "The default genome has some bad genes" << std::endl << std::endl;
    }
    else {
        std::cout << "The default genome does not have any bad genes." << std::endl << std::endl;
    }
    
    // Check the dying rates for different mutation rates and threshold. (using give_birth)
    testdyingrate(1,0,10000);
    testdyingrate(20,19,10000);
    testdyingrate(20,20,10000);
    testdyingrate(20,21,10000);
    std::cout << "The theoretical values are (approximately) r1 = 0.635, r2 = 0.55, r3 = 0.44, r4 = 0.338" << std::endl;
    
    
    return 0;
}


