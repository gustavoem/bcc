// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef FITNESS_FUNCTION_H_
#define FITNESS_FUNCTION_H_

#include "ToffoliGate.h"
#include "GAMultiplier.h"
#include "PrimeList.h"

namespace FitnessFunction
{
    
    // Calculates the cost function of a Multiplier
    // The second parameter is used to limit testing to the first n primes use zero
    // test all primes
    //
    unsigned int eval (GAMultiplier *, unsigned int);
}

#endif
