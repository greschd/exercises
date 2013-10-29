// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    09.10.2013 15:52:55 CEST
// File:    timer.hpp

// Defines: class progtech::Timer, operator overload of <<
//          MEMBER FUNCTIONS (Timer):
//          constructor, no arguments: time passed will be 0
//          start():    starts time measurement
//          stop():     stops time measurement
//          duration():     gives the time passed between start() and stop(), in seconds (as double)
//          
//          operator << :   "<< var" puts var.read() in the output stream (var of class dg_timer_class)

#ifndef __TIMER_HEADER
#define __TIMER_HEADER

#include <iostream>
#include <chrono>

namespace progtech{
class Timer {
    typedef std::chrono::high_resolution_clock clock_type; // do not use #define for typedefs.
    using time_t = double;
    
public:
    Timer();
    
    operator time_t() const;
    
    void start();
    
    void stop();
    
    time_t duration() const;
private:
    std::chrono::time_point<clock_type> t1;
    std::chrono::time_point<clock_type> t2;
};
}    
#endif //__TIMER_HEADER
