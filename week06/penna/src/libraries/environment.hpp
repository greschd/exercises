// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 16:54:06 CEST
// File:    environment.hpp

// Defines: class environment_class

// STATIC VARIABLES:
// year (int) : current year
// mrate (double) : mutation rate

// MEMBER FUNCTIONS:
// nextyear: increases year by 1
// setyear: set year to a specific date (default: 0)
// setmrate: choose mrate (default: 0)


#ifndef __ENVIRONMENT_HEADER
#define __ENVIRONMENT_HEADER

class environment_class {
    
public:
    using year_t = int;
    using mut_t = double;

    void nextyear();

    void setyear(year_t = 0);

    void setmrate(mut_t = 0);

private:
    
    static year_t year;
    static mut_t mrate;

    friend class animal_class;
    friend class genome_class;
    
};

#endif //__ENVIRONMENT_HEADER
