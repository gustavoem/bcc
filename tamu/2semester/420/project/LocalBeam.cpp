// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#include "LocalBeam.h"

LocalBeam::LocalBeam (unsigned int nof_beams) : kPrimesToTestk (100), kNeighboursToGenk (100),
   kNumberOfRunsk (1), kMaxNoImprovementk (1000), kMaxIterationsk (5000)
{
    std::cout << nof_beams << std::endl;
    number_of_beams = nof_beams;
    g_number_of_primes = 40;
    output_file.open ("data.txt");
    srand (time (NULL));
}


LocalBeam::~LocalBeam ()
{
    return;
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


void LocalBeam::deleteNeighbours (std::vector<LBMultiplier *> * neighbours)
{
    unsigned int i = 0;
    while (neighbours->size () > 0)
    {
        delete (*neighbours)[0];
        neighbours->erase (neighbours->begin ());
        i++;
    }
}


LBMultiplier * LocalBeam::bestMultiplier ()
{
    unsigned int iterations = 0;
    startBeams ();

    for (unsigned int i = 0; i < current_multipliers.size (); i++)
    {
        std::cout << "Hi" << current_multipliers[i]->toString () << std::endl;
    }
    // while (tries_left && iterations < kMaxIterationsk)
    // {
    //     std::vector<LBMultiplier *> neighbours;
    //     neighbours = findNeighbours ();
    //     std::sort (neighbours.begin (), neighbours.end (), mp_compare);

    //         // if (*current_best < *(neighbours[0]))
    //         // {
    //     delete current_best;
    //     current_best = neighbours[0];
    //     neighbours.erase (neighbours.begin ());
    //     tries_left = kMaxNoImprovementk;
    //     std::cout << "New best found: " << current_best->getFitness () << ", " 
    //     << current_best->getBitFitness () << std::endl;
    //     std::cout << current_best->toString () << std::endl;
    //         // }
    //         // else
    //             // tries_left--;

    //     if (iterations % 10 == 0)
    //         std::cout << "Iteration " << iterations << " done." << std::endl;

    //     output_file << current_best->getFitness () << " " << 
    //     current_best->getBitFitness () << std::endl;

    //     deleteNeighbours (&neighbours);
    //     iterations++;
    // }
    // output_file.close ();
    return current_best;
}