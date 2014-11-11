// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 16:57:52 CET
// File:    test_barrier.cpp

#include <mpi.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    std::cout << "rank " << rank << " of " << size;
    std::cout << std::endl;


    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "rank " << rank << " of " << size << " again.";
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
