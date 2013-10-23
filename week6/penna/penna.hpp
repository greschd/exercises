// Author:  Dominik Gresch <greschd@phys.ethz.ch>
// Date:    23.10.2013 11:11:33 CEST
// File:    penna.hpp

// Defines: classes animal and genome

/*------------------------------*/
/*           ANIMAL:            */
/*------------------------------*/
// Contains the relevant information about an animal, i.e. age (type uint), state of sickness (type uint)
// (how many negative genes it has had in its lifetime) and the genome (type genome). 
// If T denotes the number of years passed in the simulation, an animal will have age T+1 (or 1) if born in the last year 
// and T+2 if born in the current year. 

// MEMBER FUNCTIONS:

// constructor: default values are age = 0, sickness = 0, genome with default genome value (all false). 
// input can be an initial age (to be set to T+2), a parent (from whom the genome will be copied) and a mutation rate (double m)
// (to generate mutations in the copying of the genome)

// setage(n): set the age of the animal to n
// readage(): reads the age of the animal
// older(): increments the age of the animal by one and updates the state of sickness (+1 if the corresponding gene is true)

// readsick(): reads the state of sickness
// setsick(n): set the state of sickness to n

// gene(): reads the genome of the animal

/*------------------------------*/
/*           GENOME:            */
/*------------------------------*/
// Contains the genome of an animal (i.e. a boole vector of size B)

// MEMBER FUNCTIONS:

// constructor: default is a vector containing false, of size = 1, the size can be given as an option
// copy constructor: copies a genome, optionally a mutation rate can be given (copying whilst flipping some random elements), 
// mutation rate in (0,1) gives the chance of a flip happening

// set(k, b): sets the k'th element (must be in (0, size of genome)) to b (b = true, false)
// read(k): reads the k'th element
// mutate(m): flips each element with probability m (double)

#ifndef __PENNA_HEADER
#define __PENNA_HEADER

class animal {};
class genome {};

#endif //__PENNA_HEADER
