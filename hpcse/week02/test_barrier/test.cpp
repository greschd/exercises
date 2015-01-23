// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    04.10.2014 16:58:05 CEST
// File:    test.cpp

#include "../barrier/barrier.hpp"
#include <iostream>

using namespace barrier;

void no_barrier() {
    for(uint i = 0; i < 100; ++i) {
        std::cout << "a";
    }
    for(uint i = 0; i < 100; ++i) {
        std::cout << "b";
    }
    for(uint i = 0; i < 100; ++i) {
        std::cout << "c";
    }
}

void with_barrier(barrier_cl& b) {
    for(uint i = 0; i < 100; ++i) {
        std::cout << "a";
    }
    b.wait();
    for(uint i = 0; i < 100; ++i) {
        std::cout << "b";
    }
    b.wait();
    for(uint i = 0; i < 100; ++i) {
        std::cout << "c";
    }
}

int main(int argc, char* argv[]) {
    std::cout << "without barrier:" << std::endl;
    int num_threads = 4;
    std::vector<std::thread> threads(num_threads);
    
    for(int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(no_barrier);
    }
    
    for(std::thread& t: threads) {
        t.join();
    }
    
    barrier_cl b(num_threads);
    std::cout << "\nwith barrier:" << std::endl;
    for(int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(with_barrier, std::ref(b));
    }
    
    for(std::thread& t: threads) {
        t.join();
    }
    return 0;
}
