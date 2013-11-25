#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <genome.hpp>

namespace Penna
{

/*
 * Animal having a genome and age.
 */
class Animal
{
public:
    typedef Genome::age_type age_type;
    typedef Genome::randgen_type randgen_type;
    static const age_type maximum_age = Genome::number_of_genes;

    static void set_bad_threshold( age_type t );
    static void set_maturity_age( age_type r );

    // Default constructor: Uses all good genome.
    Animal();
    // Constructor using a given genome.
    Animal( const Genome& gen );

    bool is_dead() const; // the first gene is evaluated at age 0, not 1
    bool is_mature() const;
    age_type age() const;
    Genome const & get_genome() const; // return the Animal's Genome

    // Make the animal grow older by n years (default: 1).
    void grow(age_type = 1);
    // Create a baby animal inheriting its genome from this except for some random mutations.
    Animal give_birth(randgen_type & G);
    
private:
    // Number of bad genes an animal can tolerate. Parameter T in Penna's paper. (Standard: 0)
    static age_type bad_threshold_;
    // Maturity age. Parameter R in Penna's paper. (Standard: 0)
    static age_type maturity_age_;

    Genome gen_;
    age_type age_;
};

} // end namespace Penna

#endif // !defined ANIMAL_HPP
