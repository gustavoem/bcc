// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef GA_MULTIPLIER_H_
#define GA_MULTIPLIER_H_

#include "ToffoliGate.h"
#include "Multiplier.h"
#include <vector>

class GAMultiplier : Multiplier
{
    private:

    public:

        // Default constructor
        //
        GAMultiplier ();
        

        // Constructor with number of random toffoli gates
        //
        GAMultiplier (std::vector<ToffoliGate *>);


        // Default destructor
        //
        virtual ~GAMultiplier ();

        
        // Makes a crossover with another individual
        //
        void crossOver (GAMultiplier *);
};

#endif
