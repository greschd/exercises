// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    10.04.2014 01:11:35 CEST
// File:    baseline_greschd_impl.hpp

#ifndef __BASELINE_GRESCHD_impl_HEADER
#define __BASELINE_GRESCHD_impl_HEADER


#include <global.hpp>

#include <vector>
#include <algorithm>
#include <cassert>
#include <math.h>

namespace mc_potts {
    
    struct grid {
        
        template<int L1, int L2, typename MATRIX>
        class impl {
        
        public:
        //------------------------Constructor-------------------------------//
            impl(): grid_() {};
        
        //------------------------get - set---------------------------------//
            
            spin_ret_type get(index_type const & x, index_type const & y) const {
                return grid_.get(x, y);
            }
            
            spin_ret_type get_xnn(index_type const & x, index_type const & y) const {
                return  get((x - 1 + L1) % L1, y) + get((x + 1) % L1, y);
            }
            
            spin_ret_type get_ynn(index_type const & x, index_type const & y) const {
                return  get(x, (y - 1 + L2) % L2) + get(x, (y + 1) % L2);
            }
            
            void set(index_type const & x, index_type const & y, spin_ret_type const & s) {
                grid_.set(x, y, s);
            }
            

        private:
        //------------------------private members---------------------------//
            typename MATRIX::template impl<L1, L2> grid_;
            
        };
    }; // struct grid 
    
} // namespace mc_potts


#endif //__BASELINE_GRESCHD_impl_HEADER
