// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    01.10.2014 15:04:32 CEST
// File:    riemann_serial.cpp

#include <cmath>
#include <iostream>
#include <functional>

double riemann( double const & a, 
                double const & b, 
                uint const & N, 
                std::function<double(double)> f) {
    double step = (b - a) / N;
    double x = a + 0.5 * step;
    double res = 0;
    for(uint i = 0; i < N; ++i) {
        res += f(x);
        x += step;
    }
    return res * step;
}

int main(int argc, char* argv[]) {
    uint N = atoi(argv[1]);
    std::cout << "N: " << N << ", Riemann sum: " << riemann(1, 4, N, [](double x){return std::sqrt(x)*std::log(x);}) << std::endl;
    return 0;
}
