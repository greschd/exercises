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
    
    Timer(): t1(CLOCKTYPE::now()), t2(CLOCKTYPE::now()){
    }
    
    operator double() const {
        return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
    }
    
    void start() {
        t1 = CLOCKTYPE::now();
    }
    
    void stop() {
        t2 = CLOCKTYPE::now();
    }
    
    double duration() const {
        return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
    }
    
private:
    
    std::chrono::time_point<CLOCKTYPE> t1;
    std::chrono::time_point<CLOCKTYPE> t2;
};

std::ostream & operator<<(std::ostream & os, Timer const & arg) {
    os << "The time that has passed is " << arg.duration() << " seconds. ";
    return os;
}
}

#endif //__TIMER_HEADER
