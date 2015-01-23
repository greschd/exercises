// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 20:59:00 CET
// File:    function_pointer.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../src/lib/timer/dg_timer.hpp"
#include "../src/lib/function_pointer/simpson.hpp"

result_type one(argument_type const & x) {
    return 1;
}

result_type onex(argument_type const & x) {
    return x;
}

result_type xsquare(argument_type const & x) {
    return x*x;
}

result_type mysin(argument_type const & x) {
    return std::sin(x);
}

#define FUNCTION_DEF 
#define SIMPSONCALL simpson_functionpointer(FUN, a, b, n_new)
#include "../src/lib/measure/measure.hpp"



int main(int argc, char* argv[]) {
    
    measure("res_fp.txt");
    return 0;
}
