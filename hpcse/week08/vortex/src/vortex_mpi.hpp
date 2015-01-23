// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    17.11.2014 11:37:42 CET
// File:    vortex_mpi.hpp

#ifndef __VORTEX_MPI_HEADER
#define __VORTEX_MPI_HEADER

#include "common.hpp"
#include "mpi_helpers.hpp"

#include <mpi.h>
#include <vector>
#include <iostream>
#include <functional>

class VortexSheet_MPI {
public:
    // gamma_fct is the gamma(x) from eq. (10)
    // N must be divisible by P
    VortexSheet_MPI(count_t const & N,
                    std::function<val_t(val_t const &)> gamma_fct,
                    int const & rank,
                    int const & size):
                        M_(N / size),
                        particles_(M_),
                        sum_(M_),
                        tmp_particles_(M_),
                        rank_(rank),
                        size_(size) {
        val_t h = 1 / val_t(N);
        val_t x = -0.5 + ((0.5 + rank_ * M_) * h);
        for(auto & p: particles_) {
            p.x = x;
            p.y = 0;
            p.gamma = h * gamma_fct(x);
            x += h;
        }


        // setting up buffers
        int size_double;
        MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
        buffer_size_ = 3 * M_ * size_double;
        send_buffer_ = new char[buffer_size_];
        rec_buffer_ = new char[buffer_size_];
    }

    ~VortexSheet_MPI() {
        delete[] send_buffer_;
        delete[] rec_buffer_;
    }

    void print() const {
        for(count_t i = 0; i < size_; ++i) {
            if(i == rank_) {
                if(rank_ == 0) {
                    std::cout << "x, y, gamma" << std::endl;
                }
                for(auto p: particles_) {
                    std::cout << p.x << ", " << p.y << ", " << p.gamma << std::endl;
                }
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
    }

    void iterate(count_t const & steps, val_t const & dt) {
        for(count_t i = 0; i < steps; ++i) {
            tmp_particles_ = std::vector<Particle>(particles_);
            sum_ = std::vector<complex_t>(M_);
            for(count_t j = 0; j < size_; ++j) {
                send();
                // k - index for particles_ & sum_
                for(count_t k = 0; k < M_; ++k) {
                    // l - index for tmp_particles
                    for(count_t l = 0; l < M_; ++l) {
                        if(j != 0 or l != k) {
                            sum_[k] += tmp_particles_[l].gamma / (particles_[k].pos() - tmp_particles_[l].pos());
                        }
                    }
                }
                fetch();
            }

            // update with sum
            for(count_t k = 0; k < M_; ++k) {
                particles_[k].pos(particles_[k].pos() - (complex_t(0, dt)/(2 * pi)) * sum_[k]);
            }
        }
    }

    void send() {
        w_ = Wait();
        // PACK
        int pos(0);
        for(auto & p: tmp_particles_) {
            MPI_Pack(&p.x, 1, MPI_DOUBLE, send_buffer_, buffer_size_, &pos, MPI_COMM_WORLD);
            MPI_Pack(&p.y, 1, MPI_DOUBLE, send_buffer_, buffer_size_, &pos, MPI_COMM_WORLD);
            MPI_Pack(&p.gamma, 1, MPI_DOUBLE, send_buffer_, buffer_size_, &pos, MPI_COMM_WORLD);
            assert(pos <= buffer_size_);
        }

        // SEND
        if(rank_ % 2 == 0) {
            MPI_Isend(send_buffer_, buffer_size_, MPI_PACKED, (rank_ == size_ - 1) ? 0 : (rank_ + 1), (rank_ == size_ - 1) ? 0 : (rank_ + 1), MPI_COMM_WORLD, &w_.r[0]);
            MPI_Irecv(rec_buffer_, buffer_size_, MPI_PACKED, (rank_ == 0) ? (size_ - 1) : (rank_ - 1), rank_, MPI_COMM_WORLD, &w_.r[1]);
        }
        else {
            MPI_Irecv(rec_buffer_, buffer_size_, MPI_PACKED, (rank_ == 0) ? (size_ - 1) : (rank_ - 1), rank_, MPI_COMM_WORLD, &w_.r[1]);
            MPI_Isend(send_buffer_, buffer_size_, MPI_PACKED, (rank_ == size_ - 1) ? 0 : (rank_ + 1), (rank_ == size_ - 1) ? 0 : (rank_ + 1), MPI_COMM_WORLD, &w_.r[0]);
        }
    }

    void fetch() {
        // UNPACK
        w_.wait_recv();
        int pos(0);
        for(auto & p: tmp_particles_) {
            MPI_Unpack(rec_buffer_, buffer_size_, &pos, &p.x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(rec_buffer_, buffer_size_, &pos, &p.y, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(rec_buffer_, buffer_size_, &pos, &p.gamma, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            assert(pos <= buffer_size_);
        }
    }

private:
    const count_t M_;

    std::vector<Particle> particles_;
    std::vector<complex_t> sum_;
    std::vector<Particle> tmp_particles_;

    const int rank_;
    const int size_;

    int buffer_size_;
    char* send_buffer_;
    char* rec_buffer_;

    Wait w_;
};

#endif //__VORTEX_MPI_HEADER
