#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>

GeneticAlgorithm::GeneticAlgorithm (unsigned int population_size) : kControlBitsLimitk (60), kGatesLimitk (20)
{
    this->population_size = population_size;

    for (unsigned int i = 0; i < population_size; i++)
    {
        GAMultiplier * new_individual = createRandomIndividual ();
        population.push_back (new_individual);
    }
}


void GeneticAlgorithm::startPopulation ()
{
}


GeneticAlgorithm::~GeneticAlgorithm ()
{
    return;
}


Multiplier * GeneticAlgorithm::bestMultiplier ()
{
    std::vector<ToffoliGate *> gates;
    ToffoliGate * test_gate = new ToffoliGate (30, 0);
    ToffoliGate * test_gate2 = new ToffoliGate (30, 2);
    ToffoliGate * test_gate3 = new ToffoliGate (30, 16);
    gates.push_back (test_gate);
    gates.push_back (test_gate2);
    gates.push_back (test_gate3);
    GAMultiplier * mp = new GAMultiplier (gates);
    // population.push_back (mp);
    // GAMultiplier * mp = createRandomIndividual ();
    // std::cout << "value: " << FitnessFunction::eval (mp, 1000);
    
    unsigned int best_score = 0;
    unsigned int best_index = 0;

    for (unsigned int i = 0; i < population.size (); i++)
    {
        unsigned int score = FitnessFunction::eval (population[i], 1000);
        if (score > best_score)
        {
            best_score = score;
            best_index = i;
        }
    }

    std::cout << "Best score: " << best_score << std::endl;
}


GAMultiplier * GeneticAlgorithm::createRandomIndividual ()
{
    std::cout << "Generating random individual\n";

    unsigned int nof_gates = rand () % kGatesLimitk;
    std::vector<ToffoliGate *> gates;

    for (unsigned int i = 0; i < nof_gates; i++)
    {
        std::cout << "rand: " << weightedRandom () << std::endl;
        unsigned int controlled_bit = weightedRandom () * 15 + (rand () % 2) * 15 * weightedRandom ();
        ToffoliGate * tf_gate = new ToffoliGate (30, controlled_bit);

        unsigned int nof_control_points = rand () % kControlBitsLimitk / 2;
        for (unsigned int j = 0; j < nof_control_points / 2; j++)
            tf_gate->setControl (rand () % 2, weightedRandom () * 16);
        
        for (unsigned int j = 0; j < nof_control_points / 2; j++)
            tf_gate->setControl (rand () % 2, weightedRandom () * 16 + 15);

        gates.push_back (tf_gate);

        std::cout << "gate: " << tf_gate->toString () << std::endl;
    }
        
    return new GAMultiplier (gates);
}


float GeneticAlgorithm::weightedRandom ()
{
    return pow (exp (rand () / (float) RAND_MAX) / 2.73, 2);
}
