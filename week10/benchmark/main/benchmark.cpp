// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.11.2013 03:03:14 CET
// File:    benchmark.cpp

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <timer/dg_timer.hpp> /// uses variable name tool::timer

typedef unsigned int size_type;
typedef int val_type;
typedef std::set<val_type> set_type;

// creates an array of size n, setting the entries to be equal to the index 
// and then copies it to a container of type T
template<class T>
T initialize(size_type const & n) {
    assert(n >= 0);
    val_type* array = new val_type[n];
    for(size_type i = 0; i < n; ++i) {
        array[i] = i;
    }
    T container(n);
    std::copy(array, array + n , container.begin());
    return container;
}

// specialization for sets
template<>
set_type initialize(size_type const & n) {
    assert(n >= 0);
    val_type* array = new val_type[n];
    for(size_type i = 0; i < n; ++i) {
        array[i] = i;
    }
    set_type container(array, array + n);
    return container;
}

// inserts and erases an element at a random position in the container n times
template<class T, class G>
void insert_erase(T & container, size_type const & n, G & rng) {
    size_type N = container.size();
    assert(N > 0);
    std::uniform_int_distribution<size_type> distr(0,N - 1);
    for(size_type i = 0; i < n; ++i) {
        size_type j = distr(rng);
        auto it = container.begin();
        std::advance(it, j);
        it = container.insert(it, -1);
        container.erase(it);
    }
}

// executes the timing measurement
template<class T, class G>
void measure(size_type const & container_size, size_type const & k, G & rng) {
    auto container = initialize<T>(container_size);
    tool::timer.start();
    insert_erase(container, k, rng);
    tool::timer.stop();
    std::cout <<  tool::timer << std::endl;
}

int main(int argc, char* argv[]) {
    std::mt19937 rng;
    rng.seed(42);
    size_type container_size;
    std::cout << "enter a system size" << std::endl;
    std::cin >> container_size;
    size_type k = 1000000;
    
    // timing the vector
    std::cout << "vector timing:" << std::endl;
    measure<std::vector<val_type>>(container_size, k, rng);
    
    // timing the list
    std::cout << "list timing:" << std::endl;
    measure<std::list<val_type>>(container_size, k, rng);
    
    // timing the set
    std::cout << "set timing:" << std::endl;
    measure<set_type>(container_size, k, rng);
        
    return 0;
}
