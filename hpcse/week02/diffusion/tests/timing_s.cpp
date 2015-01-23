// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing_s.cpp

#include "../src/serial.hpp"

#define FUNCTION_CALL serial::iter(rho_t, tau, D, delta, num_steps)
#include "timing.cpp"

