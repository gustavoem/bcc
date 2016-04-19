// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <stdlib.h>

#include "ToffoliGate.h"
#include "GAMultiplier.h"
#include "FitnessFunction.h"


class GeneticAlgorithm
{
    private:
    
        // Stores the population size
        //
        unsigned int population_size;


        // Stores the population
        //
        std::vector<GAMultiplier *> population;


        // Creates a random individual
        //
        GAMultiplier * createRandomIndividual ();


        // Parameters for genetic algorithm
        //
        const unsigned int kGatesLimitk; 
        const unsigned int kControlBitsLimitk;

        
        // This is a distribution that looks exponential the has more weight for values
        // between 0 and 0.5 than of 0.5 to 1
        //
        float weightedRandom ();

    public:

        // Default constructor
        //  
        GeneticAlgorithm (unsigned int);
        

        // Default destructor
        //
        virtual ~GeneticAlgorithm ();


        // Finds the best multiplier
        //        
        Multiplier * bestMultiplier ();
};

#endif
