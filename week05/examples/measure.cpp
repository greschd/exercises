// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 14:34:06 CET
// File:    equilibrate.cpp

#include "../src/serial.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    rng_t rng(42);

    count_t Nx(atoi(argv[1]));
    count_t Ny(atoi(argv[2]));
    val_t d0(atof(argv[3]) / Nx);
    val_t alpha(1. / Nx - d0);
    count_t Sequi(atoi(argv[4]));
    count_t S(atoi(argv[5]));

    std::vector<std::vector<count_t>> res;
    count_t num_measure = 10;

    System disks(Nx, Ny, d0, alpha, rng);
    // equilibrate

    disks.sweep(Sequi);
    res.push_back(disks.measure());
    for(count_t i = 0; i < num_measure - 1; ++i) {
        disks.sweep(S);
        res.push_back(disks.measure());
    }

    
    std::vector<std::pair<val_t, val_t>> avg;
    // compute avg and variance
    for(count_t i = 0; i < 512; ++i) {
        count_t sum(0);
        count_t sqsum(0);
        count_t current;
        
        for(count_t j = 0; j < num_measure; ++j) {
            current = res[j][i];
            sum += current;
            sqsum += current * current;
        }

        avg.push_back(std::pair<val_t, val_t>(sum / val_t(num_measure), (sqsum - sum * sum / val_t(num_measure)) / val_t(num_measure)));
    }

    std::cout << "[" << std::endl;
    for(count_t i = 0; i < 512 - 1; ++i) {
        std::cout << "(" << avg[i].first << ", " << avg[i].second << "), ";
    }
    std::cout << "(" << avg[511].first << ", " << avg[511].second << ")]" << std::endl;
    
    return 0;
}
