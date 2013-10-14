// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    12.10.2013 12:09:00 CEST
// File:    cache.cpp
// POST:    Creates output files for the time measurement of a looping over arrays of size <= 2^20, incrementing 10^7 elements in different step sizes.

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "arrayloop.hpp"
#include "../timer/dg_timer.hpp"

void measurement(uint N, uint limit, uint step, std::string output){
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
        os << pow(2, i) << " " << times.at(i) / (N) << std::endl;
    }
    os.close();
}

int main(int argc, char* argv[]) {
    // Input - use this part if you want to put in the varibles manually
    //~ uint N, step, limit;
    //~ std::string output;
    //~ std::cout << "Enter number of incremented elements, upper limit of the array size, step size and name of the output file" << std::endl;
    //~ std::cin >> N >> limit >> step >> output;
    //~ measurement(N, limit, step, output);
    
    // calling the measurement function for different step sizes, saving in output-1.txt through output-8.txt
    
    // setting step sizes
    std::vector<uint> steps(8);
    for(uint i = 0; i < 5; ++i) {
        steps.at(i) = i + 1;
    }
    for(uint i = 5; i < 8; ++i) {
        steps.at(i) = pow(2, i - 1);
    }
    
    // calling the measurement function
    char b = '1';
    for(uint i = 0; i < 8; ++i) {
        std::string a = "output-";
        a.push_back(b);
        measurement(1e7, 2e6, steps.at(i), a.append(".txt"));
        std::cout << "finished " << a << std::endl;
        ++b;
    }
    
    return 0;
}

