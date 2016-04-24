#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm (unsigned int population_size) :  kGatesLimitk (20), kControlBitsLimitk (60),
    kPrimesToTestk (600)
{
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
            input >>= 1;
            output >>= 1;
            bit_index++;
        }
        
        for (unsigned int i = 0; i < gates.size (); i++)
            for (unsigned int j = 0; j < control_points.size (); j++)
                if (rand () % 2)
                    gates[i]->setControl (control_points[j].first, control_points[j].second);

        GAMultiplier * mp = new GAMultiplier (kPrimesToTestk, gates);
     
        // delete mp;
        // mp = createRandomIndividual ();
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

    while (iterations < 40000) 
    {
        // delete individual with least fitness
        GAMultiplier * dead_individual = population.back ();
        delete dead_individual;
        population.pop_back ();
        
        // std::cout << "Parent 1:\n" << population[0]->toString () << std::endl;
        // std::cout << "Parent 1 address:\n" << population[0]->toString () << std::endl;
        // crossover 
        unsigned int p1_i = 20 - weightedRandom () * 20;
        unsigned int p2_i = 60 - weightedRandom () * 60;
        
        // std::cout << "p1, p2: " << p1_i << ", " << p2_i << std::endl;
        // std::cout << "Parent 1 score:" << population[p1_i]->getFitness () << ", " <<  population[p1_i]->getBitFitness () << std::endl;
        // std::cout << "Parent 2 score:" << population[p2_i]->getFitness () << ", " << population[p2_i]->getBitFitness ()  << std::endl;
       
        std::vector<ToffoliGate *> child_gates = 
            population[p1_i]->getCrossoverWith (population[p2_i]);
        GAMultiplier * new_individual = new GAMultiplier (kPrimesToTestk, child_gates);
        if (new_individual->getFitness () > population[0]->getFitness ())
            std::cout << "Better child for p1i and p2i:" << p1_i << ", " << p2_i << std::endl;
        insertIndividual (new_individual);

        // std::cout << "Child:\n" << new_individual->toString () << std::endl;
        // std::cout << "New score: " << new_individual->getFitness () << ", " << population[p1_i]->getBitFitness ()  << std::endl;
        
        iterations++;
        if (iterations % 1000 == 0)
        {
            std::cout << "Iteration " << iterations << " done.\n" ;
            std::cout << "Best score: " << population[0]->getFitness () << std::endl;
        }
         
        unsigned int best_score = population[0]->getFitness ();
        output_file << best_score << " " << population[0]->getBitFitness () << "\n";
        
        // this is impirical
        if (best_score > 2 && g_number_of_primes < 25)
        {
            std::cout << "Changed prime list to 25 primes" << std::endl;
            g_number_of_primes = 25;
        }
    }
    output_file.close ();
    return population[0];
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
