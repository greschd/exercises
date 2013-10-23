// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 23:02:08 CEST
// File:    random.cpp

#include <iostream>
#include <random/random.hpp>

namespace dg_random{
using ulong = long unsigned int;

Generator::Generator(ulong const & x0) : xc(x0) {
}

ulong Generator::operator ()() {
    return xc = (a * xc + c) % m;
}

ulong const & Generator::max() {
    return m;
}

ulong const Generator::m(4294967296);
ulong const Generator::a(1664525);
ulong const Generator::c(1013904223);

}
