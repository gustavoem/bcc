// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GA_MULTIPLIER_H_
#define GA_MULTIPLIER_H_

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "PrimeList.h"
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>

#define MAX_GATES_PER_COLUMN 5

class GAMultiplier : public Multiplier
{
    private:

        // Stores the fitness of this value
        // The fitness function is the number of successful multiplications
        //
        unsigned int score;


        // Stores the score by bit
        // This score is the number pairs of bits of output and expected output
        // When all bits of a multiplication are correct the score is summed by 30 * 2
        // When n < 30 bits are correct the score is summed by n
        //
        unsigned int bit_score;

        // Stores the number of primes that should be tested to evaluate this multiplier
        //
        unsigned int eval_reps;


        // Determines the fitness of this multiplier
        // 
        void eval ();


    public:

        // Default constructor
        //
        GAMultiplier (unsigned int);
        

        // Constructor with number of random toffoli gates
        //
        GAMultiplier (unsigned int, std::vector<ToffoliGate *>);


        // Default destructor
        //
        virtual ~GAMultiplier ();

        
        // Makes a crossover with another individual
        //
        void crossOver (GAMultiplier *);


        // Score getter
        //
        unsigned int getFitness ();


        // Returns a vector of gates that would compose a crossover of this multiplier
        //  with another one 
        //
        std::vector<ToffoliGate *> getCrossoverWith (GAMultiplier *);


        // Defines the comparator, which is given by the fitness of the multiplier
        //
        bool operator < (const GAMultiplier&) const;  
};

#endif
