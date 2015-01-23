// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 21:04:34 CET
// File:    functions.hpp

#ifndef __FUNCTIONS_HEADER
#define __FUNCTIONS_HEADER


#include <math.h>

struct one {
    typedef double argument_type;
    typedef double return_type;
    
    return_type operator()(argument_type x) {
        return 1;
    }
};

struct onex {
    typedef double argument_type;
    typedef double return_type;
    
    return_type operator()(argument_type x) {
        return x;
    }
};

struct xsquare {
    typedef double argument_type;
    typedef double return_type;
    
    return_type operator()(argument_type x) {
        return x * x;
    }
};

struct mysin {
    typedef double argument_type;
    typedef double return_type;
    
    return_type operator()(argument_type x) {
        return std::sin(x);
    }
};

#endif //__FUNCTIONS_HEADER

