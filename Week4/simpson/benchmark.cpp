// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    11.10.2013 16:43:17 CEST
// File:    benchmark.cpp

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
    //~ std::ifstream input;
    //~ input.open("input.txt");
    //~ if (input.is_open()) {
        //~ double in;
        //~ while(input.eof() == false){
           //~ input >> in;
           //~ bins.push_back(in);
       //~ }
    //~ }
    //~ else std::cout << "unable to open input.txt" << std::endl;
    
    
    
    // Output test
    uint n = bins.size();
    for(uint i = 0; i < n; ++i) {
        std::cout << bins.at(i) << std::endl;
    }
    
     
    return 0;
}

