// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 23:02:08 CEST
// File:    random.cpp

#include <iostream>
#include <random/random.hpp>

namespace progtech { namespace random {
    
using rantom_t = long unsigned int;

Generator::Generator(rantom_t const & x0) : xc(x0) {
}

rantom_t Generator::operator ()() {
    return xc = (a * xc + c) % m;
}

rantom_t const & Generator::max() {
    return m;
}

rantom_t const Generator::m(4294967296);
rantom_t const Generator::a(1664525);
rantom_t const Generator::c(1013904223);

}}
