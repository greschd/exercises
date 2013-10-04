// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    03.10.2013 15:40:53 CEST
// File:    simpson.hpp

// Function:Simpson
// PRE:     Input:      A function pointer on a function taking a double and returning a double
//                      2 doubles a, b
//                      An integer N > 0.
// POST:    Output is the integral over (a,b) of the function using the Simpson integration rule over N bins.
// Depends on:          libraries iostream, math.h, assert.h

#ifndef __SIMPSON_HEADER
#define __SIMPSON_HEADER

double simpson(double (*)(double), double, double, int);

#endif //__SIMPSON_HEADER
