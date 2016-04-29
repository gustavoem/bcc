#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm (unsigned int population_size) :  kGatesLimitk (20), kControlBitsLimitk (60),
    kPrimesToTestk (600)
{
    if (population_size < 5)
        population_size = 5;

    this->population_size = population_size;
    startPopulation ();
    output_file.open ("data.txt");
    srand (time (NULL));
}


void GeneticAlgorithm::startPopulation ()
{
    // std::cout << "Starting population: " << std::endl;
    for (unsigned int i = 0; i < population_size; i++)
    {
        unsigned int p1i = rand () % (g_number_of_primes / 2);
        unsigned int p2i = p1i + rand () % (g_number_of_primes - p1i);
        unsigned int prime1 = primes[p1i];
        unsigned int prime2 = primes[p2i];
        
        GAMultiplier * mp;
        if (i > 5)
            mp = createRandomIndividual ();
        else
            mp = new GAMultiplier (kPrimesToTestk, prime1, prime2);
        
        population.push_back (mp);
    }
    std::sort (population.begin (), population.end (), mp_compare);
}


bool GeneticAlgorithm::multiplierCompare::operator () 
    (GAMultiplier * lhs, GAMultiplier * rhs) const 
{
    // we  want > 
    return *rhs < *lhs; 
}


GeneticAlgorithm::~GeneticAlgorithm ()
{
    for (unsigned int i = 0; i < population.size (); i++)
        delete population[i];
}


// Population is not so big so let's not care about exploiting the fact that
// the vector is almost sorted
void GeneticAlgorithm::insertIndividual (GAMultiplier * new_individual)
{
    population.push_back (new_individual);
    std::sort (population.begin (), population.end (), mp_compare);
}


GAMultiplier * GeneticAlgorithm::bestMultiplier ()
{
    unsigned int iterations = 0;

    while (iterations < 50000) 
    {
        // delete individual with least fitness
        GAMultiplier * dead_individual = population.back ();
        delete dead_individual;
        population.pop_back ();
        
        // crossover + mutation
        unsigned int p1_i = 20 - weightedRandom () * 20;
        unsigned int p2_i = 60 - weightedRandom () * 60;
        std::vector<ToffoliGate *> child_gates = 
            population[p1_i]->getCrossoverWith (population[p2_i]);
        GAMultiplier * new_individual = new GAMultiplier (kPrimesToTestk, child_gates);

        // update population
        if (new_individual->getFitness () > population[0]->getFitness ())
            std::cout << "Better child for p1i and p2i:" << p1_i << ", " << p2_i << std::endl;
        insertIndividual (new_individual);
        unsigned int best_score = population[0]->getFitness ();
        output_file << best_score << " " << population[0]->getBitFitness () << "\n";
        iterations++;
        

        if (iterations % 1000 == 0)
        {
            std::cout << "Iteration " << iterations << " done.\n" ;
            std::cout << "Best score: " << population[0]->getFitness () << std::endl;
        }
        // this is impirical
        if (best_score > 2 && g_number_of_primes < 25)
        {
            std::cout << "Changed prime list to 25 primes" << std::endl;
            g_number_of_primes = 25;
        }
        if (best_score > 3 && g_number_of_primes < 40)
        {
            std::cout << "Changed prime list to 40 primes" << std::endl;
            g_number_of_primes = 40;
        }
    }
    output_file.close ();

    GAMultiplier * answer = population[0];
    population[0] = NULL;
    return answer;
}


GAMultiplier * GeneticAlgorithm::createRandomIndividual ()
{
    // std::cout << "Generating random individual\n";
    unsigned int nof_gates = rand () % kGatesLimitk;
    std::vector<ToffoliGate *> gates;

    for (unsigned int i = 0; i < nof_gates; i++)
    {
        // std::cout << "rand: " << weightedRandom () << std::endl;
        unsigned int controlled_bit = weightedRandom () * 15 + (rand () % 2) * 15 * weightedRandom ();
        ToffoliGate * tf_gate = new ToffoliGate (controlled_bit);

        unsigned int nof_control_points = rand () % kControlBitsLimitk / 2;
        for (unsigned int j = 0; j < nof_control_points / 2; j++)
            tf_gate->setControl (rand () % 2, weightedRandom () * 16);
        for (unsigned int j = 0; j < nof_control_points / 2; j++)
            tf_gate->setControl (rand () % 2, weightedRandom () * 16 + 15);

        gates.push_back (tf_gate);
        // std::cout << "gate: " << tf_gate->toString () << std::endl;
    }
    return new GAMultiplier (kPrimesToTestk, gates);
}


float GeneticAlgorithm::weightedRandom ()
{
    return pow (exp (rand () / (float) RAND_MAX) / 2.73, 2);
}
