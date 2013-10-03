// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    02.10.2013 10:05:37 CEST
// File:    array2.cpp

#include <iostream>


int main(int argc, char* argv[]) {
    // asking for the input size
    uint n;
    std::cout << "How many numbers would you like to put in ?" << std::endl;
    std::cin >> n;
    
    // allocating the array and input, computing the sum
    double *a = new double[n];
    double sum = 0;
    std::cout << "Which numbers would you like to put in?" << std::endl;
    for(uint i = 0; i < n; ++i) {
        std::cin >> a[i]; // Non - numeric input will be converted to 0.
        sum += a[i];
    }

    // give error message if sum == 0
    if(sum == 0) {
        std::cout << "The array cannot be normalised since the sum of the elements is zero." << std::endl;
        return 0;
    }
    
    // normalising the array
    for(uint i = 0; i < n; ++i) {
        a[i] /= sum;
    }
    
    // output
    for(uint i = 0; i < n; ++i) {
        std::cout << a[n-1-i] << " "; 
    }
    std::cout << std::endl;
    
    delete[] a;
    
    return 0;
}
