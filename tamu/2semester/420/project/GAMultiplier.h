// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GA_MULTIPLIER_H_
#define GA_MULTIPLIER_H_

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "PrimeList.h"
#include "BitEntropy.h"
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>
#include <set>

#define MAX_GATES_PER_COLUMN 5

class GAMultiplier : public Multiplier
{
    private:

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


        // Set of all correct combination of primes that this gate is guaranteed to
        // multilpy correctly
        // 
        std::set<std::pair <unsigned int, unsigned int> > correct_answers;

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


        // Makes a mutation on a vector of gates adding or removing a gate
        // When adding a gate it shoudl control the bit that has most variations
        // 1->0 or 0->1 and we should control this gate with bits that varies the least
        //
        void mutate (std::vector<ToffoliGate *> *);

        // Score getters
        //
        unsigned int getFitness ();
        unsigned int getBitFitness ();


        // Returns a vector of gates that would compose a crossover of this multiplier
        //  with another one 
        //
        std::vector<ToffoliGate *> getCrossoverWith (GAMultiplier *);


        // Defines the comparator, which is given by the fitness of the multiplier
        //
        bool operator < (const GAMultiplier&) const;  
};

#endif
