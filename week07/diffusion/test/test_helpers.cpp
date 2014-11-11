// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 16:01:08 CET
// File:    test_helpers.cpp

#include "../src/mpi_helpers.hpp"

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

    // test broadcast
    std::vector<double> a;
    if(rank== 0) {
        a = {1, 2, 3, 4, 5};
    }

    broadcast(a, rank == 0);
    std::cout << "rank: " << rank << ", list: ";
    for(auto x: a) {
        std::cout << x << ", ";
    }
    std::cout <<  std::endl;

    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << std::flush;
    MPI_Barrier(MPI_COMM_WORLD);
    //~ std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // test send
    std::vector<double> b;
    if(rank== 0) {
        b = {6, 7, 8, 9, 10};
    }

    send(b, 0, 2, 99);
    std::cout << "rank: " << rank << ", list: ";
    for(auto x: b) {
        std::cout << x << ", ";
    }
    std::cout <<  std::endl;

    broadcast(b, rank == 0);
    
    MPI_Finalize();
    return 0;
}
