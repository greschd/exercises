// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    06.10.2014 00:37:45 CEST
// File:    serial_test.cpp

#include "../src/diffusion_mpi.hpp"

#include <mpi.h>
#include <cmath>
#include <iostream>


int main(int argc, char* argv[]) {
    
    MPI_Init(&argc, &argv);
    
    count_t mesh_size = 128;
    val_t tau = 0.00001;
    val_t D = 1;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


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
    count_t num_steps(0.5 / tau);
    //~ std::cout << "rank " << rank << ",2" << std::endl; // DEBUG
    //~ system.print();
    system.iterate(num_steps);    
    //~ system.print();
    system.iterate(num_steps);    
    //~ system.print();
    system.iterate(num_steps);    
    system.iterate(num_steps);    
    //~ system.print();

    MPI_Finalize();
    
    return 0;
}
