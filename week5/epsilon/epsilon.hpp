// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    16.10.2013 12:01:45 CEST
// File:    epsilon.cpp

#ifndef __EPSILON_HEADER
#define __EPSILON_HEADER


template <class type>
type epsilon() {
    // Checking the boundary value 
    if(type(1) + type(1) == type(1))
        return type(0);
    
    // Computing epsilon 
    type a(1);
    for(; 1 + a != 1; a /= 2);
   
    
    return a * 2;
}

#endif //__EPSILON_HEADER


