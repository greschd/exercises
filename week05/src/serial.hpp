// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 17:57:40 CET
// File:    serial.hpp

#ifndef __SERIAL_HEADER
#define __SERIAL_HEADER

#include "common.hpp"

#include <cmath>
#include <random>
#include <vector>
#include <iostream>

namespace serial {

    class System {
    public:
        System( count_t const & Nx,
                count_t const & Ny,
                val_t const & d0,
                val_t const & alpha,
                rng_t & rng):
                N_(Nx * Ny),
                d0sq_(d0 * d0),
                alpha_(alpha),
                hist_factor_(512. / (0.5 - d0sq_)),
                disks_(std::vector<Point>(Nx * Ny)),
                rng_(&rng),
                movedistr_(-alpha, alpha),
                selectdistr_(0, N_ - 1){

            // initial positions
            val_t deltax = 1. / Nx;
            val_t deltay = (std::sqrt(3) / 2.) * deltax;
            
            for(count_t i = 0; i < Ny; ++i) {
                for(count_t j = 0; j < Nx; ++j) {
                    disks_[i * Nx + j].x = deltax * (j + 0.5 * (i % 2));
                    disks_[i * Nx + j].y = deltay * i;
                }
            }
        }

        void print() const {
            std::cout << "[";
            for(count_t i = 0; i < N_ - 1; ++i) {
                std::cout << "(" << disks_[i].x << ", " << disks_[i].y << "), ";
            }
            std::cout << "(" << disks_[N_ - 1].x << ", " << disks_[N_ - 1].y << ")]" << std::endl;
        }

        void sweep(count_t const & sweep_num) {
            count_t current;
            val_t xmov;
            val_t ymov;
            Point proposal;
            bool accept;

            val_t xdist;
            val_t ydist;

            for(count_t i = 0; i < sweep_num * N_; ++i) {
                // select disk & move
                accept = true;
                current = selectdistr_(*rng_);
                xmov = movedistr_(*rng_);
                ymov = movedistr_(*rng_);
                // create proposed new position
                proposal = disks_[current];
                proposal.x = to_01(proposal.x + xmov);
                proposal.y = to_01(proposal.y + ymov);

                // check all other disks
                for(count_t j = 0; j < N_; ++j) {
                    if(j == current) {
                        continue;
                    }
                    xdist = to_dist(disks_[j].x - proposal.x);
                    ydist = to_dist(disks_[j].y - proposal.y);
                    if((xdist * xdist + ydist * ydist) < d0sq_) {
                        accept = false;
                        break;
                    }
                }
                if(accept) {
                    disks_[current] = proposal;
                }
            }
        }

        std::vector<count_t> measure() const {
            std::vector<count_t> res(512, 0);
            for(count_t i = 0; i < N_ - 1; ++i) {
                for(count_t j = i + 1; j < N_; ++j) {
                    ++res[hist_index(disks_[i], disks_[j])];
                }
            }
            return res;
        }

        

    private:
        val_t to_dist(val_t x) const{
            return std::min(x - std::floor(x), std::ceil(x) - x);
        }

        val_t to_01(val_t x) const {
            return x - std::floor(x);
        }

        val_t hist_index(Point a, Point b) const {
            val_t xdist(to_dist(a.x - b.x));
            val_t ydist(to_dist(a.y - b.y));
            xdist *= xdist;
            ydist *= ydist;
            return std::floor((xdist + ydist - d0sq_) * hist_factor_);
        }


        // private variables
        const count_t N_;
        const val_t d0sq_;
        const val_t alpha_;
        const val_t hist_factor_;
        
        std::vector<Point> disks_;

        // for random number generation
        rng_t* rng_;
        std::uniform_real_distribution<val_t> movedistr_;
        std::uniform_int_distribution<count_t> selectdistr_;
    };
} // end namespace serial

#endif //__SERIAL_HEADER

