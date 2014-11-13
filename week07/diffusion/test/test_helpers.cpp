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
    std::vector<std::vector<double>> vec;
    std::vector<double> a(5);
    std::vector<double> b(5);
    vec.push_back(a);
    vec.push_back(b);
    std::vector<Exchange> ex;
    if(rank== 0) {
        vec[0] = {1, 2, 3, 4, 5};
        //~ Exchange(a, b, 0, 1, 99);
        ex.push_back(Exchange(vec[0], vec[1], 0, 1, 99));
        //~ Exchange e0(a, b, 0, 1, 99);
        //~ Exchange e(a, b, 0, 1, 99);
        //~ Exchange e(e0);
        for(auto e: ex) {
            e.send();
            e.fetch();
        }
        //~ ex[0].send();
        //~ ex[0].fetch();
        a = {1.1, 2.1, 3.1, 4.1, 5.1};
        //~ e.send();
        //~ e.fetch();
        ex[0].send();
        ex[0].fetch();
    }
    else if(rank == 1) {
        vec[1] = {5, 4, 3, 2, 1};
        Exchange e(vec[1], vec[0], 1, 0, 99);
        e.send();
        e.fetch();
        b = {5.1, 4.1, 3.1, 2.1, 1.1};
        e.send();
        e.fetch();
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int curr_rank(0);
    while (curr_rank < size) {
        if (rank == curr_rank) {
            std::cout << "rank: " << rank << std::endl;
            std::cout << "a: ";
            for(auto x: vec[0]) {
                std::cout << x << ", ";
            }
            std::cout << std::endl << "b: ";
            for(auto x: vec[1]) {
                std::cout << x << ", ";
            }
            std::cout << std::endl;
       }
    ++curr_rank;
    //~ std::cout << curr_rank << " of " << size << std::endl;
    MPI_Barrier (MPI_COMM_WORLD);
    }
    //~ std::cout << rank << std::endl;

    
    MPI_Finalize();
    return 0;
}
