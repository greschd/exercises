// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    25.03.2014 00:42:33 CET
// File:    test.cpp

#include <beta.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    
    using namespace mc_potts;
    
    constexpr int size = 30;
    
    sim::impl<size, size, addon::custom_mt_rng, grid, matrix> testsim(1e-8, 100, 1, 200);
    testsim.print();
    testsim.thermalize();
    for(uint i = 0; i < 10; ++i) {
        testsim.update();
        testsim.measure();
    }
    
    result_struct energy = testsim.energy();
    std::cout << energy.n << std::endl;
    std::cout << energy.mean << std::endl;
    std::cout << energy.dev << std::endl;
    std::cout << energy.err << std::endl;
    testsim.print();
    
    return 0;
}
