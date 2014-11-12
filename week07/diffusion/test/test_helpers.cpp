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
    std::vector<double> a(5);
    std::vector<double> b(5);
    if(rank== 0) {
        a = {1, 2, 3, 4, 5};
        exchange(a, b, 1, 99);
    }
    else if(rank == 1) {
        b = {5, 4, 3, 2, 1};
        exchange(b, a, 0, 99);
    }
    
    for(auto x: a) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    for(auto x: b) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    
    MPI_Finalize();
    return 0;
}
