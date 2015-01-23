// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    16.10.2013 12:05:26 CEST
// File:    main.cpp

#include <iostream>
#include <limits>
#include "epsilon.hpp"
#include <typeinfo>

template <typename T>
void print() {
    std::cout << "The values for epsilon of " << typeid(T).name() << " are: \n" << "\t" << epsilon<T>() << " from the epsilon function \n \t"
              << std::numeric_limits<T>::epsilon() << " from the standard library" << std::endl;
}

int main(int argc, char* argv[]) {
    print<float>();
    print<double>();
    print<long double>();
    return 0;
}
