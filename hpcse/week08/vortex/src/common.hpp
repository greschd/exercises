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
    val_t x;
    val_t y;
    val_t gamma;

    complex_t pos() const {
        return complex_t(x, y);
    }

    complex_t const & pos(complex_t const & p) {
        x = p.real();
        y = p.imag();
        return p;
    }
};

#endif //__COMMON_HEADER
