// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include "ToffoliGate.h"
#include "GAMultiplier.h"
#include "FitnessFunction.h"

class GeneticAlgorithm
{
    private:

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
