// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    11.10.2013 16:43:17 CEST
// File:    benchmark.cpp
// PRE:     The input.txt file contains a set of unsigned integers 
// POST:    The output.txt file will contain both the given input uints 
//          and the time the simpsonsquare function needs to integrate 
//          from 0 to 10 for that number of bins

#include <iostream>
#include <fstream>
#include <vector>
#include "simpsonsquare.hpp"
#include "../timer/dg_timer.hpp" // uses the variable name "timer"
#include "../input/inputtovector.hpp"

int main(int argc, char* argv[]) {
    
    // loading the number(s) of bins from input.txt into the vector bins
    std::vector<int> bins;
    inputtovector<int>("input.txt", bins);

    // creating the vectors used to save the times and results
    uint n = bins.size();
    std::vector<double> times(n);
    std::vector<double> results(n);

    // timing the simpsonsquare function (integration range (0,10))
    for(uint i = 0; i < n; ++i) {
        timer.start();
        results.at(i) = simpsonsquare(0, 10, bins.at(i));
        timer.stop();
        times.at(i) = timer.read();
    }
    
    std::ofstream os;
    os.open("output.txt");
    os << "bins time result" << std::endl; 
    if (os.is_open()){
        for(uint i = 0; i < n; ++i) {
            os << bins.at(i) << " " << times.at(i) << " " << results.at(i) << std::endl;
        }
    }
    else std::cout << "Could not open output file." << std::endl;
    
    return 0;
}

