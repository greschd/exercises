// Author:  Dominik Gresch <greschd@gmx.ch>
// Date:    29.10.2014 18:11:21 CET
// File:    timing.cpp

#include "../src/omp.hpp"
#include "../src/serial.hpp"
#include "../src/serial_v2.hpp"

#include <set>
#include <chrono>
#include <iostream>

using namespace IMPL_TYPE;

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

    double sweep_time(0);
    double measure_time(0);
    // create clock
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    
    // equilibrate
    disks.sweep(Sequi);

    // measure
    for(count_t i = 0; i < num_measure; ++i) {
        // sweep clock
        start = std::chrono::high_resolution_clock::now();
        disks.sweep(S);
        end = std::chrono::high_resolution_clock::now();
        sweep_time += std::chrono::duration<double>(end - start).count();
        // end sweep clock

        disks.print()
        
        // measure clock
        start = std::chrono::high_resolution_clock::now();
        res.push_back(disks.measure());
        end = std::chrono::high_resolution_clock::now();
        measure_time += std::chrono::duration<double>(end - start).count();
        // end measure clock
    }

    std::cout << "sweep time: " << sweep_time << ", measure time: " << measure_time << std::endl;

    
    return 0;
}
