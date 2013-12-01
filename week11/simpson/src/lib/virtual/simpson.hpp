// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 21:16:11 CET
// File:    simpson.hpp

#include <math.h>

#ifndef __SIMPSON_HEADER
#define __SIMPSON_HEADER

typedef double result_type;
typedef double argument_type;
typedef unsigned int bin_type;


class func_class {
public:
    virtual result_type operator()(argument_type const &) const = 0;
};

class one: public func_class {
public:
    result_type operator()(argument_type const & x) const {
        return 1;
    }
};

class onex: public func_class {
public:
    result_type operator()(argument_type const & x) const {
        return x;
    }
};

class xsquare: public func_class {
public:
    result_type operator()(argument_type const & x) const {
        return x * x;
    }
};

class mysin: public func_class {
public:
    result_type operator()(argument_type const & x) const {
        return std::sin(x);
    }
};

result_type simpson_virtual(func_class const & func, argument_type const & a, argument_type const & b, const bin_type & N) {
    // Computing the step between two bins
    const argument_type step = (b - a) / N;
    
    // Compute the Simpson numerical integration: first, the parts in the middle of the bin
    result_type sum(0);
    const  argument_type a_new = a + step / 2;
    for(bin_type i = 0; i < N ; ++i){
        sum += func(a_new + i * step);
        }
    sum *= 2; 
    
    // Adding the rest, except the boundaries
    for(bin_type j = 1; j < N; ++j){
        sum += func(a + j * step);
        }
    
    // Adding the boundaries & factor, return
    return (sum + (func(a) + func(b)) / 2) * step / 3;
    
}

#endif //__SIMPSON_HEADER
