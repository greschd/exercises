// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 14:13:51 CET
// File:    timing.cpp

#include "../src/common.hpp"
#include "../src/vortex_mpi.hpp"

#include <chrono>
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

    const count_t N(atoi(argv[1]));
    const count_t num_steps(atoi(argv[2]));

    const val_t dt(0.01);

    VortexSheet_MPI test(N, gamma, rank, size);
    
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // wait for everyone to catch up before starting the clock
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) {
        // start clock
        start = std::chrono::high_resolution_clock::now();
    }
    test.iterate(num_steps, dt);
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0) {
    // end clock
        end = std::chrono::high_resolution_clock::now();
        double runtime(std::chrono::duration<double>(end - start).count());
        std::cout << "nproc: " << size << ", N: " << N << ", dt: " << dt << ", steps: " << num_steps << ", time: " << runtime << std::endl;
    }

    MPI_Finalize();

    return 0;
}
