#include "GeneticAlgorithm.h"
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm (unsigned int population_size) : kControlBitsLimitk (60), kGatesLimitk (20)
{
    this->population_size = population_size;

    for (unsigned int i = 0; i < population_size; i++)
    {
        GAMultiplier * new_individual = createRandomIndividual ();
    }
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
    GAMultiplier mp (gates);
    std::cout << "value: " << FitnessFunction::eval (&mp, 0);
}


GAMultiplier * GeneticAlgorithm::createRandomIndividual ()
{
    unsigned int nof_gates = rand () % kGatesLimitk;
    std::vector<ToffoliGate *> gates;

    for (unsigned int i = 0; i < nof_gates; i++)
    {
        unsigned int controlled_bit = rand () % 30;
        ToffoliGate * tf_gate = new ToffoliGate (30, controlled_bit);

        unsigned int nof_control_points = rand () % kControlBitsLimitk;
        for (unsigned int j = 0; j < nof_control_points; j++)
            tf_gate->setControl (rand () % 2, rand () % 30);
        
        gates.push_back (tf_gate);
    }
    
    return new GAMultiplier (gates);
}
