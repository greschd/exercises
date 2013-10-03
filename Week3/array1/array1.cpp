// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    02.10.2013 10:05:37 CEST
// File:    array1.cpp

#include <iostream>

int main(int argc, char* argv[]) {
    //allocating the array and input, computing the sum
    double a[10];
    double sum = 0;
    std::cout << "Which 10 numbers would you like to put in?" << std::endl;
    for(uint i = 0; i < 10; ++i) {
        std::cin >> a[i]; // Non - numeric input will be converted to 0.
        sum += a[i];
    }

    // give error message if sum == 0
    if(sum == 0) {
        std::cout << "The array cannot be normalised since the sum of the elements is zero." << std::endl;
        return 0;
    }
    
    //normalising the array
    for(uint i = 0; i < 10; ++i) {
        a[i] /= sum;
    }
    
    //output
    for(uint i = 0; i < 10; ++i) {
        std::cout << a[9-i] << " "; 
    }
    std::cout << std::endl;
    
    return 0;
}
