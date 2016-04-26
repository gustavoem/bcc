// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef LOCAL_BEAM_H_
#define LOCAL_BEAM_H_

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include "ToffoliGate.h"
#include "LBMultiplier.h"
#include "PrimeList.h"

class LocalBeam
{
    private:
        
        // Stores the best multiplier seen in the algorithm
        // 
        LBMultiplier * current_best;


        // Stores all opened nodes
        //
        // There should be number_of_beams elements in this vector
        //
        std::vector<LBMultiplier *> current_multipliers;


        // Stores the number of beams
        // 
        unsigned int number_of_beams;

        
        // Starts all the beams
        //
        void startBeams ();


        // Creates a first multiplier which is an empty multiplier
        //
        LBMultiplier * newBeam ();


        // Parameters for genetic algorithm
        //
        const unsigned int kPrimesToTestk;
        const unsigned int kNeighboursToGenk;
        const unsigned int kNumberOfRunsk;
        const unsigned int kMaxNoImprovementk;
        const unsigned int kMaxIterationsk;


        // Defines a multiplier comparator
        //
        struct multiplierCompare
        {
            bool operator () (LBMultiplier *, LBMultiplier *) const;
        } mp_compare;


        // Finds kNumberOfRunsk of random neighbours of a multiplier
        //
        std::vector<LBMultiplier *> findNeighbours (LBMultiplier *);


        // Deletes all the multipliers inside the vector
        //
        void deleteNeighbours (std::vector<LBMultiplier *> *);


        // Stores the file stream to the output file
        //
        std::ofstream output_file;

    public:

        // Default constructor
        //  
        LocalBeam (unsigned int);
        

        // Default destructor
        //
        virtual ~LocalBeam ();


        // Finds the best multiplier
        //        
        LBMultiplier * bestMultiplier ();
};

#endif
