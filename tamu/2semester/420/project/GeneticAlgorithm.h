// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <stdlib.h>

#include "ToffoliGate.h"
#include "GAMultiplier.h"
#include "PrimeList.h"
#include <set>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>

class GeneticAlgorithm
{
    private:
    
        // Stores the population size
        //
        unsigned int population_size;
        
        
        // Defines a multiplier comparator. This is used to mainain the population ordered
        // by fitness
        //
        struct multiplierCompare 
        {
            bool operator() (GAMultiplier *, GAMultiplier *) const;
        } mp_compare;

        
        // Stores the population
        // 
        // OBS: Keep this sorted
        //
        std::vector<GAMultiplier *> population;


        // Creates a random individual
        //
        GAMultiplier * createRandomIndividual ();


        // Parameters for genetic algorithm
        //
        const unsigned int kGatesLimitk; 
        const unsigned int kControlBitsLimitk;
        const unsigned int kPrimesToTestk;

        
        // This is a distribution that looks exponential the has more weight for values
        // between 0 and 0.5 than of 0.5 to 1
        //
        float weightedRandom ();


        // Creates the first population with multipliers that work for at least one case
        // We do this by choosing 2 random primes in our list of primes and making a  
        // multiplier that work for this case
        //
        void startPopulation ();


        // Inserts new individual in the correct place, keeping population ordered by 
        // individual fitness
        //
        void insertIndividual (GAMultiplier *);


        // Stores the file stream to the output file
        //
        std::ofstream output_file;

    public:

        // Default constructor
        //  
        GeneticAlgorithm (unsigned int);
        

        // Default destructor
        //
        virtual ~GeneticAlgorithm ();


        // Finds the best multiplier
        //        
        GAMultiplier * bestMultiplier ();
};

#endif
