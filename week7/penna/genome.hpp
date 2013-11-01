#ifndef GENOME_HPP
#define GENOME_HPP

#include <bitset>
#include <limits>


namespace Penna
{

typedef unsigned int age_type;

/*
 * Genome class. Each gene is represented by one bit.
 */
class Genome
{
public:
    // Up to this size bitset is a lot faster
    static const age_type number_of_genes = 
        std::numeric_limits<unsigned long>::digits;

    static void set_mutation_rate( age_type );

    // Default constructor: Initialize genes to all good.
    Genome();

    // Check if i'th gene is bad. (index starts at 0)
    bool is_bad( age_type ) const;
    // Count number of bad genes in first n years. (index starts at 0)
    age_type count_bad( age_type ) const;
    // Generate a copy of this, except for M flipped genes.
    Genome mutate() const;

private:
    typedef std::bitset<number_of_genes> gene_type;

    // Parameter M in Penna's paper
    static age_type mutation_rate_;
    gene_type genes_;
};

} // end namespace Penna

#endif // !defined GENOME_HPP
