// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing_t2.cpp

#include "../src/threaded_v2.hpp"

#define FUNCTION_CALL threaded_v2::iter(rho_t, tau, D, delta, num_steps, num_threads)
#include "timing.cpp"

