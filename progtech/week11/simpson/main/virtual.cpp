// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 20:59:00 CET
// File:    function_pointer.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../src/lib/timer/dg_timer.hpp"
#include "../src/lib/virtual/simpson.hpp" 

#define FUNCTION_DEF FUN func;
#define SIMPSONCALL simpson_virtual(func, a, b, n_new)
#include "../src/lib/measure/measure.hpp"

#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X


int main(int argc, char* argv[]) {
    measure("res_v.txt");
    return 0;
}
