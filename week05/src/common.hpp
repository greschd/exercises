// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 18:01:28 CET
// File:    common.hpp

#ifndef __COMMON_HEADER
#define __COMMON_HEADER

#include <random>

typedef std::mt19937 rng_t;
typedef unsigned int count_t;
typedef double val_t;


struct Point {
    Point(val_t xval = 0., val_t yval = 0.): x(xval), y(yval) {};

    val_t x;
    val_t y;
};


#endif //__COMMON_HEADER
