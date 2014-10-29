// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 17:57:40 CET
// File:    serial.hpp

#ifndef __OMP_HEADER
#define __OMP_HEADER

#include "common.hpp"

#include <set>
#include <omp.h>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>

namespace omp {

    struct IndexedPoint {
        count_t x;
        count_t y;
        count_t index_x;
        count_t index_y;
    };

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
                grid_size_(std::floor(1 / d0)),
                
                disks_(std::vector<IndexedPoint>(Nx * Ny)),
                grid_(grid_size_, std::vector<std::set<count_t>>(grid_size_, std::set<count_t>())),

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

            // initialize grid
            for(count_t i = 0; i < N_; ++i) {
                grid_[grid_index(disks_[i].x)][grid_index(disks_[i].y)].insert(i);
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
            IndexedPoint proposal;
            count_t i_x;
            count_t i_y;
            count_t i_x_old;
            count_t i_y_old;
            for(count_t i = 0; i < sweep_num * N_; ++i) {
                // select disk & move
                current = selectdistr_(*rng_);
                xmov = movedistr_(*rng_);
                ymov = movedistr_(*rng_);
                // create proposed new position
                proposal = disks_[current];
                i_x_old = proposal.index_x;
                i_y_old = proposal.index_y;
                proposal.x = to_01(proposal.x + xmov);
                proposal.y = to_01(proposal.y + ymov);
                i_x = grid_index(proposal.x);
                i_y = grid_index(proposal.y);
                // check disks in this and neighbouring grid tiles
                if (check_neighbours(proposal, i_x, i_y) and
                    check_neighbours(proposal, ((i_x == 0) ? grid_size_ - 1: i_x - 1), i_y) and
                    check_neighbours(proposal, i_x, ((i_y == 0) ? grid_size_ - 1: i_y - 1)) and
                    check_neighbours(proposal, ((i_x == 0) ? grid_size_ - 1 : i_x - 1), ((i_y == 0) ? grid_size_ - 1 : i_y - 1)) and
                    check_neighbours(proposal, ((i_x == grid_size_ - 1) ? 0: i_x + 1), i_y) and
                    check_neighbours(proposal, i_x, ((i_y == grid_size_ - 1) ? 0: i_y + 1)) and
                    check_neighbours(proposal, ((i_x == grid_size_ - 1) ? 0 : i_x + 1), ((i_y == grid_size_ - 1) ? 0 : i_y + 1))) {
                    // all checks passed -> accept proposal
                    if(i_x != i_x_old or i_y != i_y_old) {
                        proposal.index_x = i_x;
                        proposal.index_y = i_y;
                        grid_[i_x_old][i_y_old].erase(current);
                        grid_[i_x][i_y].insert(current);
                    }
                    disks_[current] = proposal;
                }
            }
        }

        std::vector<count_t> measure() const{
            print();
            //~ std::vector<count_t> res(512);
            //~ std::vector<count_t> res_loc(512);
            //~ #pragma omp parallel for private(res_loc) 
            //~ for(count_t i = 0; i < N_ - 1; ++i) {
                //~ for(count_t j = i + 1; j < N_; ++j) {
                    //~ #pragma omp critical
                    //~ {
                    //~ std::cout << i << ", " << j << ", " << hist_index(disks_.at(i), disks_.at(j)) << std::endl;
                        //~ 
                    //~ }
                    //~ ++res_loc.at(hist_index(disks_.at(i), disks_.at(j)));
                //~ }
            //~ }
            //~ #pragma omp critical
            //~ {
                //~ for(count_t i = 0; i < 512; ++i) {
                    //~ res[i] += res_loc[i];
                //~ }
            //~ }
            //~ return res;
            return std::vector<count_t>();
        }
        

    private:
        // gets 1 - periodic distance (one coordinate only)
        val_t to_dist(val_t const & x) const{
            return std::min(x - std::floor(x), std::ceil(x) - x);
        }

        // maps to a value in [0,1)
        val_t to_01(val_t const & x) const {
            return x - std::floor(x);
        }

        // returns the index in the histogram of the distance ab
        count_t hist_index(IndexedPoint const & a, IndexedPoint const & b) const {
            std::cout << a.x << std::endl;
            std::cout << b.x << std::endl;
            val_t xdist(to_dist(a.x - b.x));
            val_t ydist(to_dist(a.y - b.y));
            //~ std::cout << xdist << std::endl;
            //~ std::cout << ydist << std::endl;
            xdist *= xdist;
            ydist *= ydist;

            //~ std::cout << (xdist + ydist - d0sq_) << std::endl;
            return std::floor((xdist + ydist - d0sq_) * hist_factor_);
        }

        // returns the grid index for a given coordinate
        count_t grid_index(val_t const & x) {
            return std::min(count_t(std::floor(x * grid_size_)), grid_size_ - 1);
        }

        // check if any of the points at grid tile (i, j) overlap a.
        bool check_neighbours(IndexedPoint const & a, count_t const & i, count_t const & j) const {
            val_t xdist;
            val_t ydist;
            for(auto p: grid_[i][j]) {
                xdist = to_dist(disks_[p].x - a.x);
                ydist = to_dist(disks_[p].y - a.y);
                if((xdist * xdist + ydist * ydist) < d0sq_) {
                    return false;
                }
            }
            return true;
        }


        // private variables
        const count_t N_;
        const val_t d0sq_;
        const val_t alpha_;
        const val_t hist_factor_;
        const count_t grid_size_;
        
        std::vector<IndexedPoint> disks_;
        std::vector<std::vector<std::set<count_t>>> grid_;

        // for random number generation
        rng_t* rng_;
        std::uniform_real_distribution<val_t> movedistr_;
        std::uniform_int_distribution<count_t> selectdistr_;
    };
} // end namespace omp

#endif //__OMP_HEADER

