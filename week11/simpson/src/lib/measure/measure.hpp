// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    01.12.2013 21:55:38 CET
// File:    measure.hpp

#ifndef __MEASURE_HEADER
#define __MEASURE_HEADER


// turns a define into string
#ifndef STRINGIFY
#define STRINGIFY(X) STRINGIFY2(X)
#ifndef STRINGIFY2
#define STRINGIFY2(X) #X
#endif
#endif

void measure(std::string file_name) {
    
    FUNCTION_DEF // is used by virtual and function_object to initialize the function
    
    // getting the variables from the externally defined macros
    argument_type a = LOW;
    argument_type b = HIGH;
    bin_type N_0 = NZERO;
    bin_type N = STEPS;
    
    // making the measurement containers
    std::vector<double> results;
    std::vector<double> times;
    std::vector<bin_type> bin_sizes;
    
    
    // timing measurement
    for(bin_type i = 0; i < N; ++i) {
        result_type res = 0;
        bin_type n_new = i * N_0 + 1;
        tool::timer.start();
        for(uint i = 0; i < REPEATS; ++i) {
            res += SIMPSONCALL;
        }
        tool::timer.stop();
        results.push_back(res);
        times.push_back(tool::timer.read());
        bin_sizes.push_back(n_new);
    }
    
    
    // output 
    std::ofstream os;
    os.open(file_name, std::ios::app);
    
    std::string name = STRINGIFY(FUN);
    if(name == "one") {
        os << "N ";
        for(bin_type i = 0; i < N; ++i) {
            os << bin_sizes.at(i) << " " ;
        }
        os << std::endl;
    }
    
    os << STRINGIFY(FUN) << "_times ";
    for(bin_type i = 0; i < N; ++i) {
        os << times.at(i) << " ";
    }
    os << std::endl;
    os.close();
}

#endif //__MEASURE_HEADER
