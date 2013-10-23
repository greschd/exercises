// Programming Techniques for Scientific Simulations, HS 2013
// Exercise 6.2

#include "timer.hpp"
#include "random.hpp"

#include <iostream>

using namespace progtech;

int main() {
    
    const int N = 1000000000;
    
    Timer t;
    dg_random::Generator rnd(42);
    double s;
    
    t.start();
    for (int n=0; n<N; ++n)
        s += static_cast<double>( rnd() ) / dg_random::Generator::max();
    t.stop();
    
    s /= N;
    
    std::cout << "Mean of the random number engine is: " << s << "." << std::endl;
    std::cout << "Computed in " << t.duration() << " seconds." << std::endl;
}
