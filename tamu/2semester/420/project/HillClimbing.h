// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef HILL_CLIMBING_H_
#define HILL_CLIMBING_H_

#include <stdlib.h>

#include "ToffoliGate.h"
#include "HCMultiplier.h"
#include "PrimeList.h"
#include <iostream>
#include <fstream>
#include <time.h>

class HillClimbing
{
    private:
        
        // Stores the population
        // 
        HCMultiplier * current_best;

        
        // Starts the current_best with a circuit that works for at least
        // one pair of primes
        //
        void startIndividual ();


        // Parameters for genetic algorithm
        //
        const unsigned int kPrimesToTestk;
        const unsigned int kNeighboursToGenk;
        const unsigned int kNumberOfRunsk;
        const unsigned int kMaxNoImprovementk;


        // Defines a multiplier comparator
        //
        struct multiplierCompare
        {
            bool operator () (HCMultiplier *, HCMultiplier *) const;
        } mp_compare;


        // Finds kNumberOfRunsk of random neighbours of the urrent best
        //
        std::set<HCMultiplier *, multiplierCompare> findNeighbours ();


        // Stores the file stream to the output file
        //
        std::ofstream output_file;

    public:

        // Default constructor
        //  
        HillClimbing ();
        

        // Default destructor
        //
        virtual ~HillClimbing ();


        // Finds the best multiplier
        //        
        HCMultiplier * bestMultiplier ();
};

#endif
