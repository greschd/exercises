// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    09.04.2014 12:32:03 CEST
// File:    global.hpp

#ifndef __MC_POTTS_GLOBAL_HEADER
#define __MC_POTTS_GLOBAL_HEADER

#include <cstdint>

namespace mc_potts {
    int const S = 2; // S-state potts model
    uint8_t const n_neighbour = 4; //amount of neighbours for 2D
    
    namespace baseline_greschd {

        typedef int num_t;
        typedef int dim_t;
        typedef uint8_t spin_t;
        typedef double prob_t;
        typedef double energy_t;
        
        // J * hbar 
        const energy_t Jh = 1;
        const energy_t kb = 1;
        const energy_t physical_const = Jh / kb;
        
    } // namespace baseline_greschd
    
}//end namespace mc_potts

#endif //__MC_POTTS_GLOBAL_HEADER
