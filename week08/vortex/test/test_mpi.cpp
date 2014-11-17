// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 14:13:51 CET
// File:    test_mpi.cpp

#include "../src/common.hpp"
#include "../src/vortex_mpi.hpp"

#include <iostream>


val_t gamma(val_t x) {
    val_t y = x / 0.5;
    y *= y;
    return x / (2 * std::sqrt(1 - y));
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    VortexSheet_MPI test(10000, gamma, rank, size);
    test.print();
    for(uint i = 0; i < 20; ++i) {
        test.iterate(10, 0.01);
        test.print();
    }

    MPI_Finalize();

    return 0;
}
