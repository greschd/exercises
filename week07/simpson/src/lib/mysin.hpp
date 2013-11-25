// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    02.11.2013 14:04:47 CET
// File:    mysin.hpp

#ifndef __MYSIN_HEADER
#define __MYSIN_HEADER

#include <math.h>

class mysin {
public:
    typedef double argument_type;
    typedef double return_type;
    
    mysin(argument_type const & l): lambda_(l) {}
    
    return_type operator()(argument_type x) {
        return sin(lambda_ * x);
    }
    
private:
    const argument_type lambda_;
};

#endif //__MYSIN_HEADER

