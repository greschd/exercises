// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    12.10.2013 02:19:15 CEST
// File:    dg_inputtointvector.hpp
// Defined: Function    inputtovector<type>
// PRE:     Input:      Location of an input file as a string
//                      a std::vector<class> where "type" matches the type given in the template argument
// POST:    The function appends the data from the input file to the given vector. No guarantees can be given 
//          for what happens if the content of the input file cannot be converted to the given "type" via standard conversion nicely.

#ifndef __INPUTTOVECTOR_HEADER
#define __INPUTTOVECTOR_HEADER

#include <fstream>
#include <vector>

template <class type>
void inputtovector (const std::string & input, std::vector<type> & vector) {
    std::ifstream is;
    is.open(input);
    if (is.is_open()) {
        double in;
        while(is.eof() == false){
           is >> in;
           vector.push_back(in);
       }
    }
    else std::cout << "unable to open input file" << std::endl;
}

#endif //__INPUTTOVECTOR_HEADER

