// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    03.10.2013 15:40:53 CEST
// File:    simpsonsquare.hpp

// Function:simpsonsquare
// PRE:     Input:      2 doubles a, b 
//                      An integer N > 0.
// POST:    Output is the integral over (a,b) of x^2 using the Simpson integration rule over N bins.
// Depends on:          libraries iostream, math.h, assert.h

#ifndef __SIMPSONSQUARE_HEADER
#define __SIMPSONSQUARE_HEADER

double simpsonsquare(const double &,const double &,const int &);

#endif //__SIMPSONSQUARE_HEADER
