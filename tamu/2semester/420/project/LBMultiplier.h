// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef LB_MULTIPLIER_H_
#define LB_MULTIPLIER_H_

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "PrimeList.h"
#include "BitEntropy.h"
#include <iostream>
#include <stdlib.h>
#include <vector>


#define MAX_GATES 60

class LBMultiplier : public Multiplier
{
    private:

        // Adds a random gate to the solution
        // The new gate is placed in a high entropy bit
        //
        void addRandomGate (std::vector<ToffoliGate *> *);


        // Removes a random gate
        //
        void removeRandomGate (std::vector<ToffoliGate *> *);


        // Adds a random control point to a gate
        //
        void addRandomControlPoint (std::vector<ToffoliGate *> *);

    public:

        // Default constructor
        //
        LBMultiplier (unsigned int);
        

        // Constructor with number of random toffoli gates
        //
        LBMultiplier (unsigned int, std::vector<ToffoliGate *>);


        // Default destructor
        //
        virtual ~LBMultiplier ();

        
        // Returns a random neighbor of this multiplier
        // To get this neighbor we will either:
        // - Add a gate to this multiplier
        // - Add a control point to a gate
        //
        std::vector<ToffoliGate *> getRandomNeighbour ();

        
        // Defines the comparator, which is given by the fitness of the multiplier
        //
        bool operator < (const LBMultiplier&) const;  
};

#endif
