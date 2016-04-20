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


// We don't need to be super-careful with complexity here because there are certainly
// less than 90 gates.
std::vector<ToffoliGate *> GAMultiplier::getCrossoverWith (GAMultiplier * partner)
{
    float rel_fit1;
    std::vector<ToffoliGate *> child_gates;
    // this map has a bit index as key and a vector of all gates that controls this bit 
    std::map<unsigned int, std::vector<ToffoliGate *> *> parents1_gates; 
    std::map<unsigned int, std::vector<ToffoliGate *> *> parents2_gates; 

    // starts the map
    for (unsigned int i = 0; i < 30; i++)
    {
        parents1_gates[i] = new std::vector<ToffoliGate *> ();
        parents2_gates[i] = new std::vector<ToffoliGate *> ();
    }
    
    // calculate relative fitness
    if (this->score == 0 && partner->score == 0)
        rel_fit1 = .5;
    else
        rel_fit1 = this->score / (this->score + partner->score);
    
    // fill gate map
    for (unsigned int i = 0; i < this->gates.size (); i++)
    {
        unsigned int gate_control_bit = this->gates[i]->getControlBit ();
        parents1_gates[gate_control_bit]->push_back (this->gates[i]);
    }
    for (unsigned int i = 0; i < partner->gates.size (); i++)
    {
        unsigned int gate_control_bit = partner->gates[i]->getControlBit ();
        parents2_gates[gate_control_bit]->push_back (partner->gates[i]);
    }

    // decides which columns of gate to add
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> selected_column;
        std::vector<ToffoliGate *> * column1 = parents1_gates[i];
        std::vector<ToffoliGate *> * column2 = parents2_gates[i];
        if (column1->size () + column2->size () < MAX_GATES_PER_COLUMN)
        {
            selected_column = *column1;
            selected_column.insert (selected_column.end (), column2->begin (), column2->end ());
        }
        else if ((rand () / (float) RAND_MAX) < rel_fit1)
            selected_column = *column1;
        else
            selected_column = *column2;

        // copies gates to the answer
        for (unsigned int j = 0; j < selected_column.size (); j++)
            child_gates.push_back (new ToffoliGate (*(selected_column[j])));
    }
    return child_gates;
}

bool GAMultiplier::operator < (const GAMultiplier& other) const 
{
    return this->score < other.score;
}
