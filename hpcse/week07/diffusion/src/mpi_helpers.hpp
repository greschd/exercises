// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    11.11.2014 15:48:51 CET
// File:    mpi_helpers.hpp

#ifndef __MPI_HELPERS_HEADER
#define __MPI_HELPERS_HEADER


#include <mpi.h>
#include <vector>
#include <cassert>

typedef double val_t;

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
class Exchange {
public:
    Exchange(   std::vector<val_t> & send_vec,
                std::vector<val_t> & rec_vec,
                int const & rank,
                int const & receiver,
                int const & tag):
                    send_vec_(send_vec),
                    rec_vec_(rec_vec),
                    rank_(rank),
                    receiver_(receiver),
                    tag_(tag),
                    w_() {
        // get buffers
        int size_double;
        MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
        send_buffer_size_ = send_vec.size() * size_double;
        rec_buffer_size_ = rec_vec.size() * size_double;
        send_buffer_ = new char[send_buffer_size_];
        rec_buffer_ = new char[rec_buffer_size_];
    };

    Exchange(Exchange const & A):
        send_vec_(A.send_vec_),
        rec_vec_(A.rec_vec_),
        rank_(A.rank_),
        receiver_(A.receiver_),
        tag_(A.tag_),
        w_(),
        send_buffer_size_(A.send_buffer_size_),
        rec_buffer_size_(A.rec_buffer_size_) {
            send_buffer_ = new char[send_buffer_size_];
            rec_buffer_ = new char[rec_buffer_size_];   
                };

    ~Exchange() {
        delete[] send_buffer_;
        delete[] rec_buffer_;
    }

    void send() {
        // PACK send_vec
        w_ = Wait();
        int pos(0);
        for(auto & x: send_vec_) {
            MPI_Pack(&x, 1, MPI_DOUBLE, send_buffer_, send_buffer_size_, &pos, MPI_COMM_WORLD);
            assert(pos <= send_buffer_size_);
        }
        if(rank_ % 2 == 0) {
            MPI_Isend(send_buffer_, send_buffer_size_, MPI_PACKED, receiver_, tag_, MPI_COMM_WORLD, &w_.r[0]);
            MPI_Irecv(rec_buffer_, rec_buffer_size_, MPI_PACKED, receiver_, tag_, MPI_COMM_WORLD, &w_.r[1]);
        }
        else {
            MPI_Irecv(rec_buffer_, rec_buffer_size_, MPI_PACKED, receiver_, tag_, MPI_COMM_WORLD, &w_.r[1]);
            MPI_Isend(send_buffer_, send_buffer_size_, MPI_PACKED, receiver_, tag_, MPI_COMM_WORLD, &w_.r[0]);
        }
    }

    void fetch() {
        // UNPACK
        w_.wait_recv();
        int pos(0);
        for(auto & x: rec_vec_) {
            MPI_Unpack(rec_buffer_, rec_buffer_size_, &pos, &x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            assert(pos <= rec_buffer_size_);
        }
    }

private:
    std::vector<val_t> & send_vec_;
    std::vector<val_t> & rec_vec_;
    const int rank_;
    const int receiver_;
    const int tag_;
    Wait w_;
    int send_buffer_size_;
    int rec_buffer_size_;
    char* send_buffer_;
    char* rec_buffer_;
};


#endif //__MPI_HELPERS_HEADER
