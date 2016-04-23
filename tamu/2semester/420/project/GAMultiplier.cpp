#include "GAMultiplier.h"


GAMultiplier::GAMultiplier (unsigned int eval_reps) : Multiplier ()
{
    this->eval_reps = eval_reps;
    if (eval_reps == 0)
        eval_reps = g_number_of_primes;

    bit_score = 0;
}


GAMultiplier::GAMultiplier (unsigned int eval_reps, std::vector<ToffoliGate *> gates) : 
    Multiplier (gates)
{
    this->eval_reps = eval_reps;
    if (eval_reps == 0)
        eval_reps = g_number_of_primes;

    eval ();
}


GAMultiplier::~GAMultiplier ()
{
    return;
}


unsigned int GAMultiplier::getFitness ()
{
    return this->correct_answers.size ();
}

unsigned int GAMultiplier::getBitFitness ()
{
    return this->bit_score;
}


void GAMultiplier::eval ()
{
    bit_score = 0;

    for (unsigned int i = 0; i < eval_reps; i++)
    {
        unsigned int p1i = rand () % (g_number_of_primes / 2);
        unsigned int p2i = p1i + rand () % (g_number_of_primes - p1i);
        unsigned int prime1 = primes[p1i];
        unsigned int prime2 = primes[p2i];
        // std::cout << "p1, p2: " << prime1 << ", " << prime2 << std::endl;
        unsigned int input = (prime1 << 15) + prime2;
        unsigned int output = multiply (input);
        unsigned int expected_output = prime1 * prime2;
        for (unsigned int i = 0; i < 30; i++)
        {
            // std::cout << ((output >> i) & 1) << "|" << ((expected_output >> i) & 1) << std::endl;
            bool bit_match = ((output >> i) & 1) == ((expected_output >> i) & 1);
            if (bit_match)
                bit_score++;
            
            BitEntropy::addBitOccurrence (i, bit_match);
        }
        if (output == expected_output)
        {
            bit_score *= 2; 
            correct_answers.insert (std::make_pair (prime1, prime2));
        }
    }
    bit_score >>= 7;
}


// We don't need to be super-careful with complexity here because there are certainly
// less than 90 gates.
std::vector<ToffoliGate *> GAMultiplier::getCrossoverWith (GAMultiplier * partner)
{
    float rel_fit1;
    std::vector<ToffoliGate *> child_gates;
    // this map has a bit index as key and a vector of all gates that controls this bit 
    std::map<unsigned int, std::vector<ToffoliGate *> *> parents1_gates = this->getGates ();
    std::map<unsigned int, std::vector<ToffoliGate *> *> parents2_gates = partner->getGates ();

    // calculate relative fitness
    if (this->getFitness () == 0 && partner->getFitness () == 0)
        rel_fit1 = .5;
    else
        rel_fit1 = this->getFitness () / (this->getFitness () + partner->getFitness ());
    
    
    // decides which columns of gate to add
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> selected_column;
        std::vector<ToffoliGate *> * column1 = parents1_gates[i];
        std::vector<ToffoliGate *> * column2 = parents2_gates[i];
        if (column1->size () + column2->size () < MAX_GATES_PER_COLUMN &&
            ((column1->size () + column2->size ()) % 2))
        {
            selected_column = *column1;
            selected_column.insert (selected_column.end (), column2->begin (), column2->end ());
        }
        else 
            if ((rand () / (float) RAND_MAX) < rel_fit1)
            selected_column = *column1;
        else
            selected_column = *column2;

        // copies gates to the answer
        for (unsigned int j = 0; j < selected_column.size (); j++)
            if (rand () % 2)
                child_gates.push_back (new ToffoliGate (*(selected_column[j])));
        
        // for (unsigned int i = 0; i < column1->size (); i++)
            // if ((rand () / (float) RAND_MAX) < rel_fit1)
                // child_gates.push_back (new ToffoliGate (*(*column1)[i]));
        // for (unsigned int i = 0; i < column2->size (); i++)
            // if ((rand () / (float) RAND_MAX) > rel_fit1)
                // child_gates.push_back (new ToffoliGate (*(*column2)[i]));

    }

    mutate (&child_gates);
    return child_gates;
}



void GAMultiplier::mutate (std::vector<ToffoliGate *> * gates)
{
    if (rand () % 2)      // does nothing
        return;
    else if (rand () % 2) // adds a gate based on entropy
    {
        unsigned int control_bit = BitEntropy::getHighEntropyBit ();
        ToffoliGate * new_gate = new ToffoliGate (control_bit);
        new_gate->setControl (rand () % 2, BitEntropy::getLowEntropyBit ());
        if (rand () % 2)
            new_gate->setControl (rand () % 2, BitEntropy::getLowEntropyBit ());
        if (rand () % 2)
            new_gate->setControl (rand () % 2, BitEntropy::getLowEntropyBit ());
        while (true);
        gates->push_back (new_gate);
    }
    else                  // removes a gate
    {
        gates->erase (gates->begin () + rand () % gates->size ());
    }
}



bool GAMultiplier::operator < (const GAMultiplier& other) const 
{
    return this->correct_answers.size () < other.correct_answers.size ();
}
