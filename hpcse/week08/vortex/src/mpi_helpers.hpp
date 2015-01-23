// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 15:48:51 CET
// File:    mpi_helpers.hpp

#ifndef __MPI_HELPERS_HEADER
#define __MPI_HELPERS_HEADER


#include <mpi.h>
#include <vector>
#include <cassert>


struct Wait {
    void wait() {
        MPI_Waitall(2, r, s);
    }

    void wait_recv() {
        MPI_Wait(&r[1], &s[1]);
    }

    MPI_Request r[2];
    MPI_Status s[2];
};

#endif //__MPI_HELPERS_HEADER
