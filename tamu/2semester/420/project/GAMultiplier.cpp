#include "GAMultiplier.h"


GAMultiplier::GAMultiplier (unsigned int eval_reps) : Multiplier ()
{
    this->eval_reps = eval_reps;
    score = 0;
}


GAMultiplier::GAMultiplier (unsigned int eval_reps, std::vector<ToffoliGate *> gates) : Multiplier ()
{
    this->eval_reps = eval_reps;
    if (eval_reps == 0)
        eval_reps = NUMBER_OF_PRIMES;

    this->gates = gates;
    eval ();
}


GAMultiplier::~GAMultiplier ()
{
    return;
}


unsigned int GAMultiplier::getFitness ()
{
    return this->score;
}


void GAMultiplier::eval ()
{
    unsigned int points = 0;
    // std::cout << "Number of primes: " << NUMBER_OF_PRIMES;

    for (unsigned int i = 0; i < eval_reps; i++)
    {
        unsigned int p1i = rand () % (NUMBER_OF_PRIMES / 2);
        unsigned int p2i = p1i + rand () % (NUMBER_OF_PRIMES - p1i);
        unsigned int prime1 = primes[p1i];
        unsigned int prime2 = primes[p2i];
        // std::cout << "p1, p2: " << prime1 << ", " << prime2 << std::endl;
        unsigned int input = (prime1 << 15) + prime2;
        if (multiply (input) == prime1 * prime2)
            score++;
    }
    
    this->score = points;
}


std::vector<ToffoliGate *> getCrossoverWith (GAMultiplier * partner)
{
    std::vector<ToffoliGate *> crossover_gates;
    return crossover_gates;
}
