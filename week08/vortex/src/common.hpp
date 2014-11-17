// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 11:40:16 CET
// File:    common.hpp

#ifndef __COMMON_HEADER
#define __COMMON_HEADER

#include <complex>

typedef int count_t;
typedef double val_t;
typedef std::complex<val_t> complex_t;

const val_t pi(3.14159265358979323);

struct Particle {
    complex_t pos;
    val_t gamma;
};

#endif //__COMMON_HEADER
