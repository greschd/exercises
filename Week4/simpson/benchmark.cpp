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
//~ #include "../input/inputtovector.hpp"  // Un - comment if you want to use an input file for the number of bins

int main(int argc, char* argv[]) {
    
    // loading the number(s) of bins from input.txt into the vector bins
    // Un-comment this part if you want to put in the number of bins from an input file.
    //~ std::vector<int> bins;
    //~ inputtovector<int>("input.txt", bins);
    
    // Creating the vector containing the number of bins 
    // Comment this part if you want to put in the number of bins from an input file.
    std::vector<int> bins(139);
    for(uint i = 0; i < 9 ; ++i) {
        bins.at(i) = i + 1;
    }
    for(uint i = 9; i < 109; ++i) {
        bins.at(i) = 10 * (i - 8);
    }
    for(uint i = 109; i < 139; ++i) {
        bins.at(i) = 1000 * (i - 108);
    }

    // creating the vectors used to save the times 
    uint n = bins.size();
    std::vector<double> times(n);

    // timing the simpsonsquare function (integration range (0,10)). 
    for(uint i = 0; i < n; ++i) {
        timer.start();
        for(uint j = 0; j < 1000; ++j) {
            simpsonsquare(0, 10, bins.at(i));
        }
        timer.stop();
        times.at(i) = timer.read() / 1000;
    }
    
    // Output into output.txt
    std::ofstream os;
    os.open("output.txt");
    os << "bins time" << std::endl; 
    if (os.is_open()){
        for(uint i = 0; i < n; ++i) {
            os << bins.at(i) << " " << times.at(i) << std::endl;
        }
    }
    else std::cout << "Could not open output file." << std::endl;
    
    return 0;
}

