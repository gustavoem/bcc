// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#include "HillClimbing.h"

HillClimbing::HillClimbing () : kPrimesToTestk (600), kNeighboursToGenk (100),
   kNumberOfRunsk (1), kMaxNoImprovementk (100)
{
    srand (time (NULL));
}


HillClimbing::~HillClimbing ()
{
    return;
}


bool HillClimbing::multiplierCompare::operator () (HCMultiplier * lhs, HCMultiplier * rhs) const 
{
    return rhs < lhs;
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


std::set<HCMultiplier *, HillClimbing::multiplierCompare> HillClimbing::findNeighbours ()
{
    std::set<HCMultiplier *, multiplierCompare> neighbours;
    for (unsigned int i = 0; i < 2; i++)
        neighbours.insert (new HCMultiplier (kPrimesToTestk, current_best->getRandomNeighbour ()));

    std::set<HCMultiplier *, multiplierCompare>::iterator it = neighbours.begin ();
    while (it != neighbours.end ())
    {
        std::cout << (*it)->toString () << std::endl;
        it++;
    }
    return neighbours;
}


HCMultiplier * HillClimbing::bestMultiplier ()
{
    for (unsigned int i = 0; i < kNumberOfRunsk; i++)
    {
        unsigned int tries_left = kMaxNoImprovementk;
        startIndividual ();
        std::cout << current_best->toString () << std::endl;
        while (tries_left)
        {
            std::set<HCMultiplier *, multiplierCompare> neighbors;
            neighbors = findNeighbours ();
            tries_left = 0;
        }
    }
    return current_best;
}
