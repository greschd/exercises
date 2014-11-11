// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 15:48:51 CET
// File:    mpi_helpers.hpp

#ifndef __MPI_HELPERS_HEADER
#define __MPI_HELPERS_HEADER


#include <mpi.h>
#include <vector>
#include <cassert>

typedef double val_t;

/// T must be convertible to MPI_DOUBLE. Could be avoided, but will need
/// a conversion MPI_DATATYPE <-> int
/// send_vec and rec_vec must have the same length
void exchange(std::vector<double> & send_vec, std::vector<T> rec_vec, int const & sender, int const & receiver) {
    // get buffer
    int size_double;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
    int buffer_size = send_vec.size() * size_double;
    char* buffer = new char[buffer_size];

    // PACK
    int pos(0);
    for(auto & x: send_vec) {
        MPI_Pack(&x, 1, MPI_DOUBLE, buffer, buffer_size, &pos, MPI_COMM_WORLD);
        assert(pos <= buffer_size);
    }

    delete[] buffer;
}

/// With these I was just playing around (not used in the exercise)
template<typename T>
void broadcast(std::vector<T> & vec, bool const & sender) {

    int len;
    if(sender) {
        len = vec.size();
    }
    
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // get buffer
    int size_double;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
    int buffer_size = len * size_double;
    char* buffer = new char[buffer_size];


    // PACK
    if(sender) {
        int pos(0);
        for(auto & x: vec) {
            MPI_Pack(&x, 1, MPI_DOUBLE, buffer, buffer_size, &pos, MPI_COMM_WORLD);
            assert(pos <= buffer_size);
        }
    }

    // broadcast
    MPI_Bcast(buffer, buffer_size, MPI_PACKED, 0, MPI_COMM_WORLD);

    if(!sender){
        vec.resize(len);
        int pos(0);
        for(auto & x: vec) {
            MPI_Unpack(buffer, buffer_size, &pos, &x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        }
    }

    delete[] buffer;
}


template<typename T>
void send(std::vector<T> & vec, int const & sender, int const & receiver, int const & tag) {

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank != sender && rank != receiver) {
        return;
    }

    int len;
    if(rank == sender) {
        len = vec.size();
        MPI_Send(&len, 1, MPI_INT, receiver, tag, MPI_COMM_WORLD);
    }
    else if(rank == receiver) {
        MPI_Status status;
        MPI_Recv(&len, 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &status);
    }

    // get buffer
    int size_double;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
    int buffer_size = len * size_double;
    char* buffer = new char[buffer_size];
    
    // PACK
    if(rank == sender) {
        int pos(0);
        for(auto & x: vec) {
            MPI_Pack(&x, 1, MPI_DOUBLE, buffer, buffer_size, &pos, MPI_COMM_WORLD);
            assert(pos <= buffer_size);
        }
        MPI_Send(buffer, buffer_size, MPI_PACKED, receiver, tag, MPI_COMM_WORLD);
    }

    // broadcast
    if(rank == receiver) {
        MPI_Status status;
        MPI_Recv(buffer, buffer_size, MPI_PACKED, sender, tag, MPI_COMM_WORLD, &status);

        vec.resize(len);
        int pos(0);
        for(auto & x: vec) {
            MPI_Unpack(buffer, buffer_size, &pos, &x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        }
    }

    delete[] buffer;
}

#endif //__MPI_HELPERS_HEADER
