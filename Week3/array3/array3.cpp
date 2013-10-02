// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    02.10.2013 10:05:37 CEST
// File:    array2.cpp

#include <iostream>
#include <vector>


int main(int argc, char* argv[]) {

    
    // allocating the vector, input
    std::vector<double> a;
    std::cout << "Which numbers would you like to put in? (enter \"end\" to finish input)" << std::endl;
    std::string in;
    double sum = 0;
    while(1) {
        std::cin >> in;
        if(in == "end") 
            break;
        a.push_back(stod(in));
        sum += a.back();
    }
    
    const uint n = a.size();
    
    // normalising the array
    for(uint i = 0; i < n; ++i) {
        a[i] /= sum;
    }
    
    // output
    for(uint i = 0; i < n; ++i) {
        std::cout << a[n-1-i] << " "; 
    }
    std::cout << std::endl;
    
    return 0;
}
