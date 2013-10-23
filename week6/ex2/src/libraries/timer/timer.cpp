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

Timer::operator double() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
}

void Timer::start() {
    t1 = CLOCKTYPE::now();
}

void Timer::stop() {
    Timer::t2 = CLOCKTYPE::now();
}

double Timer::duration() const {
    return std::chrono::duration_cast<std::chrono::duration<double>>(Timer::t2 - Timer::t1).count();
}

std::ostream & operator<<(std::ostream & os, Timer const & arg) {
    os << "The time that has passed is " << arg.duration() << " seconds. ";
    return os;
}
}
