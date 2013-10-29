// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 23:02:08 CEST
// File:    random.cpp

#include <iostream>
#include <random/random.hpp>

namespace progtech { namespace random {
    
    // COMMENT: not nice. Better to use a typedef inside the class, avoid defining types in redundant way!
    using random_t = uint32_t; // if you change this you need to put the modulo back in 

    Generator::Generator(random_t const & x0) : xc(x0) {
    }

    random_t Generator::operator ()() {
        return xc = (a * xc + c);
    }

    random_t const & Generator::max() {
        return random_t(-1);
    }

    random_t const Generator::a(1664525);
    random_t const Generator::c(1013904223);

}}
