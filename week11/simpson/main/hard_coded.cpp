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

#define SIMPSON_DIRECT(FCT) \
result_type simpson_direct(const argument_type & a,argument_type const & b,bin_type const & N){\
    /* Computing the step between two bins */\
    const result_type step = (b - a) / N;\
    \
    /* Compute the Simpson numerical integration: first, the parts in the middle of the bin */\
    result_type sum(0);\
    const result_type a_new = a + step / 2;\
    for(bin_type i = 0; i < N ; ++i){\
        sum += FCT(a_new + i * step);\
        }\
    sum *= 2; \
    \
    /* Adding the rest, except the boundaries */\
    for(bin_type j = 1; j < N; ++j){\
        sum += FCT(a + j * step);\
        }\
    \
    /* Adding the boundaries & factor, return */\
    return (sum + (FCT(a) + FCT(b)) / 2) * step / 3;\
}\


SIMPSON_DIRECT(FUN)

int main(int argc, char* argv[]) {
    
    argument_type a = LOW;
    argument_type b = HIGH;
    bin_type N_0 = NZERO;
    bin_type N = STEPS;
    
    std::vector<double> results;
    std::vector<double> times;
    std::vector<bin_type> bin_sizes;
    
    for(bin_type i = 0; i < N; ++i) {
        result_type res = 0;
        bin_type n_new = i * N_0 + 1;
        tool::timer.start();
        for(uint i = 0; i < REPEATS; ++i) {
            res += simpson_direct(a, b, n_new);
        }
        tool::timer.stop();
        results.push_back(res);
        times.push_back(tool::timer.read());
        bin_sizes.push_back(n_new);
    }
    
    // to prevent the compiler from optimizing away the whole simpson function call (has proven to be unnecessary)
    //~ std::cout << STRINGIFY(FUN) << "\t";
    //~ for(bin_type i = 0; i < N; ++i) {
        //~ std::cout << results.at(i) << " "; 
    //~ }
    //~ std::cout << std::endl;
    
    std::ofstream os;
    os.open("res_h.txt", std::ios::app);
    
    std::string name = STRINGIFY(FUN);
    if(name == "one") {
        os << "N ";
        for(bin_type i = 0; i < N; ++i) {
            os << bin_sizes.at(i) << " " ;
        }
        os << std::endl;
    }
    
    os << STRINGIFY(FUN) << "_times ";
    for(bin_type i = 0; i < N; ++i) {
        os << times.at(i) << " ";
    }
    os << std::endl;
    os.close();
    return 0;
}
