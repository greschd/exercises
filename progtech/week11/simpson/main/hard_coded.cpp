// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 20:59:11 CET
// File:    hard_coded.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "../src/lib/timer/dg_timer.hpp"

typedef double result_type;
typedef double argument_type;
typedef unsigned int bin_type;

#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X

// I use inline instead of writing every function separately because it is the same when compiled.
inline result_type one(argument_type const & x)
{
    return 1;
}

inline result_type onex(argument_type const & x)
{
    return x;
}

inline result_type xsquare(argument_type const & x)
{
    return x*x;
}

inline result_type mysin(argument_type const & x) {
    return std::sin(x);
}

// macro for the simpson function. creates 
#define SIMPSON_DIRECT(FCT) \
result_type simpson_direct(const argument_type & a,argument_type const & b,bin_type const & N){\
    /* Computing the step between two bins */\
    const result_type step = (b - a) / N;\
    \
    /* Compute the Simpson numerical integration: first, the parts in the middle of the bin */\
    result_type sum(0);\
    const result_type a_new = a + step / 2;\
    for(bin_type i = 0; i < N ; ++i){\
        result_type temp = FCT(a_new + i * step);\
        sum += temp;\
        }\
    sum *= 2; \
    \
    /* Adding the rest, except the boundaries */\
    for(bin_type j = 1; j < N; ++j){\
        result_type temp = FCT(a + j * step);\
        sum += temp;\
        }\
    \
    /* Adding the boundaries & factor, return */\
    return (sum + (FCT(a) + FCT(b)) / 2) * step / 3;\
}\


SIMPSON_DIRECT(FUN)

#define FUNCTION_DEF
#define SIMPSONCALL simpson_direct(a, b, n_new)
#include "../src/lib/measure/measure.hpp" 

int main(int argc, char* argv[]) {
    
    measure("res_h.txt");
    return 0;
}
