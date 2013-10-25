// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 22:39:49 CEST
// File:    timer.cpp

#include <iostream>
#include <chrono>
#include <timer/timer.hpp>
#define CLOCKTYPE std::chrono::high_resolution_clock

namespace progtech{

Timer::Timer(): t1(CLOCKTYPE::now()), t2(CLOCKTYPE::now()){
}

using time_t = double;

Timer::operator time_t() const {
    return std::chrono::duration_cast<std::chrono::duration<time_t>>(t2 - t1).count();
}

void Timer::start() {
    t1 = CLOCKTYPE::now();
}

void Timer::stop() {
    Timer::t2 = CLOCKTYPE::now();
}

time_t Timer::duration() const {
    return std::chrono::duration_cast<std::chrono::duration<time_t>>(Timer::t2 - Timer::t1).count();
}

std::ostream & operator<<(std::ostream & os, Timer const & arg) {
    os << "The time that has passed is " << arg.duration() << " seconds. ";
    return os;
}
}
