// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    21.09.2013 18:11:04 CEST
// File:    epsilon.cpp
// The program computes the floating point precision epsilon for types float and double up to a factor of 2.

#include <iostream>

int main(int argc, char* argv[]) {
    // Checking the boundary value for float
    if(float(1) + float(1) == float(1)){
        std::cout << "Your computer is really bad.. tough luck :(" << std::endl;
    }
    // Checking the boundary value for double
    if(double(1) + double(1) == double(1)){
        std::cout << "Your computer is really bad.. tough luck :(" << std::endl;
    }
    
    // Computing epsilon for type float
    float a = 1;
    for(;1 + a != 1;a /= 2);
    std::cout << "The machine floating point precision for type float is = " << a * 2 << std::endl;
    
    // Computing epsilon for type double
    double b = 1;
    for(;1 + b != 1;b /= 2);
    std::cout << "The machine floating point precision for type double is = " << b * 2 << std::endl;
    
    return 0;
}

