#include "FitnessFunction.h"
#include <iostream>

unsigned int FitnessFunction::eval (GAMultiplier * mp, unsigned int tries)
{
    unsigned int score = 0;
    unsigned int input = 0;
    unsigned int expected_result;
    
    if (tries == 0)
        tries = 6541;

    for (unsigned int i = 1; i < 2; i++)
    {
        for (unsigned int j = 0; j < 1; j++)
        {
            std::cout << "p_i, p_j: " << primes[i] << ", " << primes[j] << std::endl;
            input = (primes[j] << 15) + primes[i];
            expected_result = primes[i] * primes[j];
            if (mp->multiply (input) == expected_result)
                score++;
        }
    }
    return score;
}
