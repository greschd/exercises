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
    std::vector<Exchange> ex;
    if(rank== 0) {
        a = {1, 2, 3, 4, 5};
        ex.push_back(Exchange(a, b, 1, 99));
        for(Exchange& e: ex) {
            e.send();
            e.fetch();
        }
        //~ for(uint i = 0; i < ex.size(); ++i) {
            //~ std::cout << 1 << std::endl;
            //~ ex[i].send();
            //~ ex[i].fetch();
        //~ }
        //~ Exchange exc(a, b, 1, 99);
        //~ ex.push_back(Exchange(a, b, 1, 99));
        //~ e.send();
        //~ e.fetch();
        a = {1.1, 2.1, 3.1, 4.1, 5.1};
        //~ for(uint i = 0; i < ex.size(); ++i) {
            //~ std::cout << 2 << std::endl;
            //~ ex[i].send();
            //~ ex[i].fetch();
        //~ }
        for(Exchange& e: ex) {
            e.send();
            e.fetch();
        }
        //~ e.send();
        //~ e.fetch();
    }
    else if(rank == 1) {
        b = {5, 4, 3, 2, 1};
        ex.push_back(Exchange(b, a, 0, 99));
        //~ for(uint i = 0; i < ex.size(); ++i) {
            //~ std::cout << 3 << std::endl;
            //~ ex[i].send();
            //~ ex[i].fetch();
        //~ }
        for(Exchange& e: ex) {
            e.send();
            e.fetch();
        }
        //~ Exchange exc(b, a, 0, 99);
        //~ ex.push_back(Exchange(b, a, 0, 99));
        //~ e.send();
        //~ e.fetch();
        b = {5.1, 4.1, 3.1, 2.1, 1.1};
        //~ for(uint i = 0; i < ex.size(); ++i) {
            //~ std::cout << 4 << std::endl;
            //~ ex[i].send();
            //~ ex[i].fetch();
        //~ }
        for(Exchange& e: ex) {
            e.send();
            e.fetch();
        }
        //~ e.send();
        //~ e.fetch();
    }


    int curr_rank(0);
    while (curr_rank < size) {
       if (rank == curr_rank) {
            std::cout << "rank: " << rank << std::endl;
            std::cout << "a: ";
            for(auto x: a) {
                std::cout << x << ", ";
            }
            std::cout << std::endl << "b: ";
            for(auto x: b) {
                std::cout << x << ", ";
            }
            std::cout << std::endl;
       }
    ++curr_rank;
    MPI_Barrier (MPI_COMM_WORLD);
    }
    //~ std::cout << rank << std::endl;

    
    MPI_Finalize();
    return 0;
}
