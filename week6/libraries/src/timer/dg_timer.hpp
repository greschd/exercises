// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    09.10.2013 15:52:55 CEST
// File:    dg_timer.hpp

// Defines: class dg_timer_class, operator overload of <<, variable timer (of type dg_timer_class)
//          MEMBER FUNCTIONS (dg_timer_class):
//          constructor, no arguments: time passed will be 0
//          start():    starts time measurement
//          stop():     stops time measurement
//          read():     gives the time passed between start() and stop(), in seconds (as double)
//          
//          operator << :   "<< var" puts var.read() in the output stream (var of class dg_timer_class)

#ifndef __DG_TIMER_HEADER
#define __DG_TIMER_HEADER

#include <iostream>
#include <chrono>
#define CLOCKTYPE std::chrono::high_resolution_clock

class dg_timer_class {
public:
    
    dg_timer_class(): t1(CLOCKTYPE::now()), t2(CLOCKTYPE::now()){
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
    
    double read() const {
        return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
    }
    
private:
    
    std::chrono::time_point<CLOCKTYPE> t1;
    std::chrono::time_point<CLOCKTYPE> t2;
};

std::ostream & operator<<(std::ostream & os, dg_timer_class const & arg) {
    os << "The time that has passed is " << arg.read() << " seconds. ";
    return os;
}

dg_timer_class timer;

#endif //__DG_TIMER_HEADER
