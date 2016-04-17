#include "FitnessFunction.h"

unsigned int FitnessFunction::eval (GAMultiplier * mp, unsigned int tries)
{
    unsigned int score = 0;
    unsigned int input;
    unsigned int expected_result;
    
    if (tries == 0)
        tries = 6541;

    for (unsigned int i = 0; i < tries; i++)
    {
        for (unsigned int j = 0; j < tries; j++)
        {
            input = i + (j << 15);
            expected_result = i * j;
            if (mp->multiply (input) == expected_result)
                score++;
        }
    }
}
