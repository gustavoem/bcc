// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#include "LocalBeam.h"

LocalBeam::LocalBeam (unsigned int nof_beams) : kPrimesToTestk (100), kNeighboursToGenk (100),
   kNumberOfRunsk (1), kMaxNoImprovementk (1000), kMaxIterationsk (100)
{
    number_of_beams = nof_beams;
    g_number_of_primes = 40;
    current_best = NULL;
    output_file.open ("data.txt");
    srand (time (NULL));
}


LocalBeam::~LocalBeam ()
{   
    delete current_best;
}


bool LocalBeam::multiplierCompare::operator () (LBMultiplier * lhs, LBMultiplier * rhs) const 
{
    return *rhs < *lhs;
}


void LocalBeam::startBeams ()
{
    for (unsigned int i = 0; i < number_of_beams; i++)
        current_multipliers.push_back (newBeam ());
}


LBMultiplier * LocalBeam::newBeam ()
{
    return new LBMultiplier (kPrimesToTestk);
}


std::vector<LBMultiplier *> LocalBeam::findNeighbours (LBMultiplier * multiplier)
{
    std::vector<LBMultiplier *> neighbours;
    for (unsigned int i = 0; i < kNeighboursToGenk; i++)
    {
        LBMultiplier * new_multiplier = 
            new LBMultiplier (kPrimesToTestk, multiplier->getRandomNeighbour ());
        neighbours.push_back (new_multiplier);
    }
    return neighbours;
}


void LocalBeam::deleteMultipliers (std::vector<LBMultiplier *> * multipliers)
{
    while (multipliers->size () > 0)
    {
        delete (*multipliers)[0];
        multipliers->erase (multipliers->begin ());
    }
}


LBMultiplier * LocalBeam::bestMultiplier ()
{
    unsigned int iterations = 0;
    startBeams ();

    while (iterations < kMaxIterationsk)
    {
        std::vector<LBMultiplier *> successors;
        for (unsigned int i = 0; i < current_multipliers.size (); i++)
        {
            std::vector<LBMultiplier *> neighbours = 
                findNeighbours (current_multipliers[i]);
            successors.insert 
                (successors.end (), neighbours.begin (), neighbours.end ());
        }

        updateMultipliers (&successors);
        if (iterations % 10 == 0)
            std::cout << "Iteration " << iterations << " done." << std::endl;

        output_file << current_multipliers[0]->getFitness () << " " << 
        current_multipliers[0]->getBitFitness () << std::endl;

        iterations++;
    }
    output_file.close ();
    deleteMultipliers (&current_multipliers);
    return current_best;
}


void LocalBeam::updateMultipliers (std::vector<LBMultiplier *> * successors)
{
    std::sort (successors->begin (), successors->end (), mp_compare);        
    if (current_best == NULL || *current_best < *((*successors)[0]))
    {
        delete current_best;
        current_best = new LBMultiplier (*((*successors)[0]));
        std::cout << "New best found with score: " << current_best->getFitness () << ", "
            << current_best->getBitFitness () << std::endl;
    }
    
    deleteMultipliers (&current_multipliers);
    current_multipliers.insert (current_multipliers.end (), successors->begin (),
                                         successors->begin () + number_of_beams);

    successors->erase (successors->begin (), successors->begin () + number_of_beams);
    deleteMultipliers (successors);
}