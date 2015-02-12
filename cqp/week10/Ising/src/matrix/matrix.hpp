// Author:  Dominik Gresch <greschd@ethz.ch>
// Date:    10.04.2014 14:10:05 CEST
// File:    int2t_v01_matrix.hpp

#ifndef __INT2T_V01_MATRIX_HEADER
#define __INT2T_V01_MATRIX_HEADER

#include <types.hpp>

#include <bitset>
#include <cassert>

namespace mc_potts {
    
    namespace detail_int2t_v01 {
        
        template<int N>
        class int2t_vec {
        public:
            int2t_vec(): vec_() {};
            
            void set(int const & i, uint8_t const & x) {
                assert(i < N && i >=0);
                vec_.set(i, (int(x) & 1) != 0);
            }
            
            spin_ret_type get(index_type const & i) const{
                assert(i < N && i >=0);
                return 0 + vec_[i];
            }
        private:
            std::bitset<N> vec_;
        };

    } // namespace detail_int2t_v01

    struct matrix {
        
        template<int L1, int L2>
        class impl {
            template<int N>
            using int2t_vec = detail_int2t_v01::int2t_vec<N>;
        public:
            impl(): mat_() {};
            
            void set(   index_type const & i, 
                        index_type const & j, 
                        index_type const & x) {
                mat_.set(i * L2 + j, x);
            }
            
            spin_ret_type get(  index_type const & i,
                                index_type const & j) const {
                return mat_.get(i * L2 + j);
            }
            
        private:
            int2t_vec<L1 * L2> mat_;
        };
        
        static std::string name() {
            return "int2t_v01_matrix";
        }

    }; // struct int2t_v01_matrix
} // namespace mc_potts

#endif //__INT2T_V01_MATRIX_HEADER
