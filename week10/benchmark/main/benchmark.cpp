// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.11.2013 03:03:14 CET
// File:    benchmark.cpp

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <timer/dg_timer.hpp> /// uses variable name timer

typedef unsigned int size_type;
typedef unsigned int val_type;

// creates an array of size n, setting the entries to be equal to the index 
// and then copies it to a container of type T
template<class T>
T initialize(size_type const & n) {
    val_type* array = new val_type[n];
    for(size_type i = 0; i < n; ++i) {
        array[i] = i;
    }
    T container(n);
    std::copy(array, array + n , container.begin());
    return container;
}

// inserts and erases an element at a random position in the container n times
template<class T, class G>
void insert_erase(T & container, size_type const & n, G & rng) {
    size_type N = container.size();
    std::uniform_int_distribution<size_type> distr(0,N-1);
    for(size_type i = 0; i < n; ++i) {
        size_type j = distr(rng);
        auto it = container.begin();
        std::advance(it, j);
        it = container.insert(it, 0);
        container.erase(it);
    }
}

int main(int argc, char* argv[]) {
    std::mt19937 rng;
    rng.seed(42);
    // timing the vector
    auto vector = initialize<std::vector<val_type>>(10000);
    timer.start();
    insert_erase(vector, 1000000, rng);
    timer.stop();
    std::cout << "Time used with a vector is "  << timer << std::endl;
    
    // timing the list
    auto list = initialize<std::list<val_type>>(10000);
    timer.start();
    insert_erase(list, 1000000, rng);
    timer.stop();
    std::cout << "Time used with a list is "  << timer << std::endl;
    
    return 0;
}
