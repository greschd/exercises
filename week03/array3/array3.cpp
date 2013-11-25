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
        a.push_back(stod(in)); // The program will crash for strange inputs, since I don't know how to catch the exception yet.
        sum += a.back();
    }
    
    // give error message if sum == 0
    if(sum == 0) {
        std::cout << "The array cannot be normalised since the sum of the elements is zero." << std::endl;
        return 0;
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
