#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>

GeneticAlgorithm::GeneticAlgorithm (unsigned int population_size) : kControlBitsLimitk (60), kGatesLimitk (20),
    kPrimesToTestk (1000)
{
    this->population_size = population_size;
    startPopulation ();
}


void GeneticAlgorithm::startPopulation ()
{
    // std::cout << "Starting population: " << std::endl;
    for (unsigned int i = 0; i < population_size; i++)
    {
        unsigned int p1i = rand () % NUMBER_OF_PRIMES;
        unsigned int p2i = p1i + rand () % (NUMBER_OF_PRIMES - p1i);
        unsigned int prime1 = primes[p1i];
        unsigned int prime2 = primes[p2i];
        unsigned int input = (prime1 << 15) + prime2;
        unsigned int output = prime1 * prime2;
        std::vector<ToffoliGate *> gates;
        std::vector< std::pair<bool, unsigned int> > control_points;
        
        // std::cout << "p1, p2: " << prime1 << ", " << prime2 << std::endl;
        unsigned int bit_index = 0;
        while (input > 0 || output > 0)
        {
            unsigned int input_bit = input % 2;
            unsigned int output_bit = output % 2;
            
            if (input_bit != output_bit)
            {
                ToffoliGate * gate = new ToffoliGate (bit_index);
                gates.push_back (gate);
                control_points.push_back (std::make_pair (input_bit, bit_index));
            }

            input /= 2;
            output /= 2;
            bit_index++;
        }
        
        for (unsigned int i = 0; i < gates.size (); i++)
            for (unsigned int j = 0; j < control_points.size (); j++)
                if (rand () % 2)
                    gates[i]->setControl (control_points[j].first, control_points[j].second);

        GAMultiplier * mp = new GAMultiplier (kPrimesToTestk, gates);
        population.insert (mp);
        // std::cout << mp->toString () << std::endl;
        // std::cout << (mp->multiply ((prime1 << 15) + prime2) == (prime1 * prime2)) << std::endl;
        // std::cout << "Fitness: " << mp->getFitness () << std::endl;
    }
}


bool GeneticAlgorithm::multiplierCompare::operator () 
    (GAMultiplier * lhs, GAMultiplier * rhs) const 
{
    return *lhs < *rhs; 
}

GeneticAlgorithm::~GeneticAlgorithm ()
{
    return;
}


Multiplier * GeneticAlgorithm::bestMultiplier ()
{
    unsigned int best_score = 0;
    unsigned int best_index = 0;
    
    std::set<GAMultiplier *>::iterator individual;
    for (individual = population.begin (); individual != population.end(); ++individual)
    {
        unsigned int score = (*individual)->getFitness ();
        if (score > best_score)
            best_score = score;
        std::cout << "Score: " << score;
    }

    std::cout << "Best score: " << best_score << std::endl;
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
