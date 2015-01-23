// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing_t1.cpp

#include "../src/threaded_v1.hpp"

#define FUNCTION_CALL threaded_v1::iter(rho_t, tau, D, delta, num_steps, num_threads)
#include "timing.cpp"
