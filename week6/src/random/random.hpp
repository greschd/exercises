// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 01:36:13 CEST
// File:    random.hpp

#ifndef __RANDOM_HEADER
#define __RANDOM_HEADER

template <class T>
class dg_random {
    
public:

    dg_random(T s0): rand(s0) {
    }
    
    unsigned int read() {
        return rand;
    }
    
    void renew() {
        rand = (a * rand + c) % m;
    }
    
    unsigned int newread() {
        renew();
        return rand;
    }
    
private:

    T rand;
    T m = 4294967296;
    T a = 1664525;
    T c = 1013904223;
};

#endif //__RANDOM_HEADER
