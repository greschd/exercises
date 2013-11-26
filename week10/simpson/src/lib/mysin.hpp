// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    02.11.2013 14:04:47 CET
// File:    mysin.hpp

#ifndef __MYSIN_HEADER
#define __MYSIN_HEADER

#include <math.h>
#include <simpson.hpp>

class mysin:  public func_class {
public:
    mysin(argument_type const & l): lambda_(l) {}
    
    func_class::f_result_type operator()(const func_class::argument_type x) const{
        return sin(lambda_ * x);
    }
    
private:
    const argument_type lambda_;
};

#endif //__MYSIN_HEADER

