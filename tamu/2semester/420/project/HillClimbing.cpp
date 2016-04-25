// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#include "HillClimbing.h"

HillClimbing::HillClimbing () : kPrimesToTestk (1000), kNeighboursToGenk (1000),
   kNumberOfRunsk (1), kMaxNoImprovementk (600), kMaxIterationsk (10000)
{
    output_file.open ("data.txt");
    srand (time (NULL));
}


HillClimbing::~HillClimbing ()
{
    return;
}


bool HillClimbing::multiplierCompare::operator () (HCMultiplier * lhs, HCMultiplier * rhs) const 
{
    return *rhs < *lhs;
}


void HillClimbing::startIndividual ()
{
    unsigned int p1i = rand () % (g_number_of_primes / 2);
    unsigned int p2i = p1i + rand () % (g_number_of_primes - p1i);
    unsigned int prime1 = primes[p1i];
    unsigned int prime2 = primes[p2i];
    unsigned int input = (prime1 << 15) + prime2;
    unsigned int output = prime1 * prime2;
    std::vector<ToffoliGate *> gates;
    std::vector< std::pair<bool, unsigned int> > control_points;
        
    std::cout << "p1, p2: " << prime1 << ", " << prime2 << std::endl;
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
        
    current_best = new HCMultiplier (kPrimesToTestk, gates);
}


std::vector<HCMultiplier *> HillClimbing::findNeighbours ()
{
    std::vector<HCMultiplier *> neighbours;
    for (unsigned int i = 0; i < kNeighboursToGenk; i++)
    {
        HCMultiplier * new_multiplier = 
            new HCMultiplier (kPrimesToTestk, current_best->getRandomNeighbour ());
        neighbours.push_back (new_multiplier);
    }

    return neighbours;
}


void HillClimbing::deleteNeighbours (std::vector<HCMultiplier *> * neighbours)
{
    unsigned int i = 0;
    while (neighbours->size () > 0)
    {
        // delete (*neighbours)[0];
        neighbours->erase (neighbours->begin ());
        i++;
    }
    std::cout << "deleted: " << i << std::endl;
}


HCMultiplier * HillClimbing::bestMultiplier ()
{
    for (unsigned int i = 0; i < kNumberOfRunsk; i++)
    {
        unsigned int tries_left = kMaxNoImprovementk;
        unsigned int iterations = 0;
        startIndividual ();
        std::cout << current_best->toString () << std::endl;
        while (tries_left && iterations < kMaxIterationsk)
        {
            std::vector<HCMultiplier *> neighbours;
            neighbours = findNeighbours ();
            std::sort (neighbours.begin (), neighbours.end (), mp_compare);
             
            if (*current_best < *(neighbours[0]))
            {
                // delete current_best;
                current_best = neighbours[0];
                neighbours.erase (neighbours.begin ());
                // std::cout << "erased someone" << std::endl;
                tries_left = kMaxNoImprovementk;
                std::cout << "New best found: " << current_best->getFitness () << std::endl;
            }
            else
                tries_left--;
            
            if (iterations % 100 == 0)
                std::cout << "Iteration " << iterations << " done." << std::endl;

            output_file << current_best->getFitness () << " " << 
                current_best->getBitFitness () << std::endl;
                
            deleteNeighbours (&neighbours);
            iterations++;
        }
    }
    output_file.close ();
    return current_best;
}
