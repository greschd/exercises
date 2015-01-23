// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 20:59:00 CET
// File:    function_pointer.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../src/lib/timer/dg_timer.hpp"
#include "../src/lib/function_object/simpson.hpp"
#include "../src/lib/function_object/functions.hpp"

#define FUNCTION_DEF FUN func;
#define SIMPSONCALL simpson_functionobject(func, a, b, n_new)
#include "../src/lib/measure/measure.hpp"


int main(int argc, char* argv[]) {
    measure("res_fo.txt");
    return 0;
}
