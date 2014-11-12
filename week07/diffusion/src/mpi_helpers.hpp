// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 15:48:51 CET
// File:    mpi_helpers.hpp

#ifndef __MPI_HELPERS_HEADER
#define __MPI_HELPERS_HEADER


#include <mpi.h>
#include <vector>
#include <cassert>

typedef double val_t;

/// send_vec and rec_vec must have the same length
void exchange(  std::vector<val_t> & send_vec,
                std::vector<val_t> & rec_vec,
                int const & receiver,
                int const & tag) {
    // get buffers
    int size_double;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
    int send_buffer_size = send_vec.size() * size_double;
    int rec_buffer_size = rec_vec.size() * size_double;
    char* send_buffer = new char[send_buffer_size];
    char* rec_buffer = new char[rec_buffer_size];

    // PACK send_vec
    int pos(0);
    for(auto & x: send_vec) {
        MPI_Pack(&x, 1, MPI_DOUBLE, send_buffer, send_buffer_size, &pos, MPI_COMM_WORLD);
        assert(pos <= send_buffer_size);
    }

    MPI_Status status;
    MPI_Sendrecv(send_buffer, send_buffer_size, MPI_PACKED, receiver, tag,
                 rec_buffer, rec_buffer_size, MPI_PACKED, receiver, tag,
                 MPI_COMM_WORLD, &status);

    // UNPACK
    for(auto & x: rec_vec) {
        int pos(0);
        MPI_Unpack(rec_buffer, rec_buffer_size, &pos, &x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        assert(pos <= rec_buffer_size);
    }
    
    delete[] send_buffer;
    delete[] rec_buffer;
}

#endif //__MPI_HELPERS_HEADER
