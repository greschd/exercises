// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.03.2014 01:28:15 CET
// File:    main.cpp

#include <iostream>
#include <vector>
#include "../src/lib/framework.cpp"
#include <boost/python.hpp>

val_t matrix_entry(index_t m, index_t n, val_t k) {
    
    op_cl H = op_cl(op_cl::adagger) * op_cl(op_cl::a) + complex_cl(0.5, 0) * op_cl(op_cl::id) + (op_cl(op_cl::a) + complex_cl(k, 0) * op_cl(op_cl::adagger))*(op_cl(op_cl::a) + op_cl(op_cl::adagger))*(op_cl(op_cl::a) + op_cl(op_cl::adagger))*(op_cl(op_cl::a) + op_cl(op_cl::adagger));
    
    return prod(wfct_cl(m), H(wfct_cl(n))).re();
}

BOOST_PYTHON_MODULE(measure_lib)
{
    using namespace boost::python;
    def("matrix_entry", matrix_entry);
}
