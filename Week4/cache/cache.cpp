// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    12.10.2013 12:09:00 CEST
// File:    cache.cpp

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "arrayloop.hpp"
#include "../timer/dg_timer.hpp"

int main(int argc, char* argv[]) {
    // Input
    uint N, step, limit;
    std::string output;
    std::cout << "Enter number of incremented elements, upper limit of the array size, step size and name of the output file" << std::endl;
    std::cin >> N >> limit >> step >> output;
    
    // timing the looping over the arrays
    std::vector<double> times;
    
    for(uint i = 1; i <= limit; i *= 2) {
        timer.start();
        arrayloop(i, step, N);
        timer.stop();
        times.push_back(timer.read());
    }

    // Output
    uint n = times.size();
    std::ofstream os;
    os.open(output);
    os << "length time_per_increment" << std::endl;
    for(uint i = 0; i < n; ++i) {
        os << pow(2, i) << " " << times.at(i) / N << std::endl;
    }
    os.close();
    
    return 0;
}

