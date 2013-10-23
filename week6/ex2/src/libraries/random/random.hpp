// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 01:36:13 CEST
// File:    random.hpp

// Defines: class Generator, which will create linear congruential random number generator 
//          X_n+1 = (a * X_n + c) mod m; with m = 4294967296, a = 1664525, c = 1013904223;
//          The seed X_0 is the value with which the generator is initialized
//          The type in which all the calculations are done is long unsigned int

//          MEMBER FUNCTIONS:
//          constructor with and without seed (default seed = 0)
//          current() reads the current random number
//          iterate() generates a new random number (X_n -> X_n+1), the old value gets discarded
//          generate() reads a new random number 

//          currentsmall() and generatesmall() have the same effect on the variable as the corresponding functions
//          current and generate, but the return will be a double normalised to be in (0,1)

#ifndef __RANDOM_HEADER
#define __RANDOM_HEADER

namespace dg_random
{


    class Generator {
        using ulong = long unsigned int;
        
    public:

        Generator(ulong const & = 0);
        
        ulong operator ()();
        
        static ulong const & max();
        
    private:

        ulong xc;
        
        static ulong const m;
        static ulong const a; 
        static ulong const c;
    };
}

#endif //__RANDOM_HEADER
