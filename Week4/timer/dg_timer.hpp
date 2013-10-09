// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    09.10.2013 15:52:55 CEST
// File:    dg_timer.hpp

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
    os << "The time that has passed is " << arg.read();
    return os;
}

dg_timer_class timer;

#endif //__DG_TIMER_HEADER
