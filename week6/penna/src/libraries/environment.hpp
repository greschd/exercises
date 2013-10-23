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

friend class animal_class;
friend class genome_class;

void nextyear();

void setyear(int = 0);

void setmrate(double = 0);

private:
    
static int year;
static double mrate;
    
};

#endif //__ENVIRONMENT_HEADER
