// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 14:34:06 CET
// File:    equilibrate.cpp

#include "../src/serial.hpp"

#include <iostream>

using namespace serial;

int main(int argc, char* argv[]) {
    rng_t rng(42);

    count_t Nx(atoi(argv[1]));
    count_t Ny(atoi(argv[2]));
    val_t d0(atof(argv[3]) / Nx);
    val_t alpha(1. / Nx - d0);
    count_t Sequi(atoi(argv[4]));

    System disks(Nx, Ny, d0, alpha, rng);
    // equilibrate
    disks.sweep(Sequi);
    disks.print();

    return 0;
}
