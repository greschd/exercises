// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    22.11.2013 18:43:43 CET
// File:    monte_carlo.cpp

#include <iostream>
#include <random>
#include <math.h>
#include <typeinfo>

typedef double length_type;
typedef double average_type;
typedef unsigned int count_type;

 // created a pair of coordinates in [0,1) and checks if the point lies inside the unit circle
template<class T> /// for different random number generators
bool new_point(T & rng) {
    std::uniform_real_distribution<length_type> distr(0,1);
    length_type x = distr(rng);
    length_type y = distr(rng);
    return (x*x + y*y) < 1;
}

bool new_point() { /// using drand48 
    length_type x = drand48();
    length_type y = drand48();
    return (x*x + y*y) < 1;
}

template<class T>
void measure(count_type N, T & rng)
{
    count_type count_in = 0;
    for(count_type i = 0; i < N; ++i) {
        if(new_point(rng)) {
            ++count_in;
        }
    }
    std::cout << "For N = " << N << ": "<<  std::endl;
    std::cout << "Pi = " <<  4 * average_type(count_in) / N << " +/- " << 4 * std::sqrt((count_in*(1 - count_in/average_type(N)))) / N  << std::endl;
    /// error of the mean is the same as the "standard" formula, but making use of the fact that the only possible values are 0 and 1
}

void measure(count_type N)
{
    count_type count_in = 0;
    for(count_type i = 0; i < N; ++i) {
        if(new_point()) {
            ++count_in;
        }
    }
    std::cout << "For N = " << N << ": "<<  std::endl;
    std::cout << "Pi = " <<  4 * average_type(count_in) / N << " +/- " << 4 * std::sqrt((count_in*(1 - count_in/average_type(N)))) / N  << std::endl;
}


int main(int argc, char* argv[]) {
    
    // setting up the mt19937 
    std::mt19937 rng;
    std::string str;
    std::cout << "enter a seed for the mersenne twister: " << std::endl;
    std::getline(std::cin,str);
    std::seed_seq seed1 (str.begin(),str.end());
    rng.seed(seed1);
    
    // seeding drand48
    short unsigned int seed2;
    std::cout << "enter a seed for drand48: " << std::endl;
    std::cin >> seed2;
    seed48(&seed2);
    
    std::cout << "from the mersenne twister:" << std::endl;
    for(uint i = 100; i <= 1e7; i*= 10) {
        measure(i, rng);
    }
    
    std::cout << "from the drand48:" << std::endl;
    for(uint i = 100; i <= 1e7; i*= 10) {
        measure(i);
    }
    
    return 0;
}
