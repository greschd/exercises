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
#define CLOCKTYPE std::chrono::high_resolution_clock


namespace progtech{
class Timer {
public:
    Timer();
    
    operator double() const;
    
    void start();
    
    void stop();
    
    double duration() const;
private:
    std::chrono::time_point<CLOCKTYPE> t1;
    std::chrono::time_point<CLOCKTYPE> t2;
};
}    
#endif //__TIMER_HEADER
