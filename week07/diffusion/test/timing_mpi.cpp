// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 01:39:05 CEST
// File:    timing.cpp

#ifndef __TIMING_HEADER
#define __TIMING_HEADER


#include "../src/diffusion_mpi.hpp"

#include <chrono>
#include <iostream>


void timing(count_t const & mesh_size,
            count_t const & num_steps, 
            val_t const & tau, 
            val_t const & D,
            count_t const & rank,
            count_t const & size) {
    
    density_t rho(mesh_size, row_t(mesh_size));
    val_t delta(2. / (rho.size() - 1));
    for(count_t i = 0; i < mesh_size; ++i) {
        for(count_t j = 0; j < mesh_size; ++j) {
            if((fabs(delta*i - 1.) < 0.5) && (fabs(delta*j - 1.) < 0.5)) {
                rho[i][j] = 1;
            }
        }
    }
    DiffusionMPI system(rho, tau, D, rank, size);

    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    // wait for everyone to catch up before starting the clock
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) {
        // start clock
        start = std::chrono::high_resolution_clock::now();
    }
    system.iterate(num_steps);
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0) {
    // end clock
        end = std::chrono::high_resolution_clock::now();
        double runtime(std::chrono::duration<double>(end - start).count());
        std::cout << "mesh: " << mesh_size << ", steps: " << num_steps << ", tau: " << tau << ", D: " << D << ", time: " << runtime << std::endl;
    }
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    count_t mesh = 128;
    count_t num_steps;
    val_t tau = 0.00001;
    val_t D(atoi(argv[1]));


    num_steps = 1e9 / (mesh * mesh);
    timing(mesh, num_steps, tau, D, rank, size);
    mesh = 256;
    num_steps = 1e9 / (mesh * mesh);
    tau = 0.000001;
    timing(mesh, num_steps, tau, D, rank, size);
    mesh = 1024;
    num_steps = 1e9 / (mesh * mesh);
    tau = 0.00000001;
    timing(mesh, num_steps, tau, D, rank, size);
    mesh = 2048;
    num_steps = 1e9 / (mesh * mesh);
    tau = 0.00000001;
    timing(mesh, num_steps, tau, D, rank, size);
    
    MPI_Finalize();
    
    return 0;
}


#endif //__TIMING_HEADER
