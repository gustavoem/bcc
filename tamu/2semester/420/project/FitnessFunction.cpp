#include "FitnessFunction.h"
#include <stdlib.h>
#include <iostream>

unsigned int FitnessFunction::eval (GAMultiplier * mp, unsigned int tries)
{
    unsigned int score = 0;
    unsigned int input = 0;
    
    if (tries == 0)
        tries = NUMBER_OF_PRIMES;
    
        // std::cout << "Number of primes: " << NUMBER_OF_PRIMES;

    for (unsigned int i = 0; i < tries; i++)
    {
        unsigned int p1i = rand () % (NUMBER_OF_PRIMES / 2);
        unsigned int p2i = p1i + rand () % (NUMBER_OF_PRIMES - p1i);
        unsigned int prime1 = primes[p1i];
        unsigned int prime2 = primes[p2i];
        // std::cout << "p1, p2: " << prime1 << ", " << prime2 << std::endl;
        // unsigned int input = (prime1 << 15) + prime2;
        if (mp->multiply (input) == prime1 * prime2)
            score++;
    }
    return score;
}
