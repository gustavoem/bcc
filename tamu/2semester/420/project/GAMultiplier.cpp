#include "GAMultiplier.h"


GAMultiplier::GAMultiplier (unsigned int eval_reps) : Multiplier (eval_reps)
{
    return;
}


GAMultiplier::GAMultiplier (unsigned int eval_reps, std::vector<ToffoliGate *> gates) : 
    Multiplier (eval_reps, gates)
{
    return;
}


GAMultiplier::GAMultiplier (unsigned int eval_reps, unsigned int prime1,
    unsigned int prime2) : Multiplier (eval_reps, prime1, prime2)
{
    return;
}


GAMultiplier::~GAMultiplier ()
{
    return;
}



// We don't need to be super-careful with complexity here because there are certainly
// less than 90 gates.
std::vector<ToffoliGate *> GAMultiplier::getCrossoverWith (GAMultiplier * partner)
{
    std::vector<ToffoliGate *> child_gates;
    float rel_fit = relativeFitness (partner);

        
    // decides which columns of gate to add
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> * selected_column;
        selected_column = crossColumn (i, partner, rel_fit);
        
        // copies gates to the answer
        for (unsigned int j = 0; j < selected_column->size (); j++)
            if (rand () % 2)
                child_gates.push_back (new ToffoliGate (*((*selected_column)[j])));

        delete selected_column;
    }

    // mutate (&child_gates);
    return child_gates;
}


std::vector<ToffoliGate *> * GAMultiplier::crossColumn (unsigned int i, 
    GAMultiplier * partner, float rel_fit)
{
    std::vector<ToffoliGate *> * selected_column = new std::vector<ToffoliGate *> ();
    std::vector<ToffoliGate *> * column1 = this->getGates ()[i];
    std::vector<ToffoliGate *> * column2 = partner->getGates ()[i];
    if (column1->size () + column2->size () < MAX_GATES_PER_COLUMN &&
            ((column1->size () + column2->size ()) % 2))
    {
        *selected_column = *column1;
        selected_column->insert (selected_column->end (), column2->begin (),
                column2->end ());
    }
    else 
        if ((rand () / (float) RAND_MAX) < rel_fit)
            *selected_column = *column1;
        else
            *selected_column = *column2;
    return selected_column;
}


float GAMultiplier::relativeFitness (GAMultiplier * partner)
{
    unsigned int fit1 = this->getFitness (); 
    unsigned int fit2 = partner->getFitness (); 
    // calculate relative fitness
    if (fit1 + fit2 == 0)
        return .5;
    else
        return fit1 / ((float) fit1 + fit2);
}


void GAMultiplier::mutate (std::vector<ToffoliGate *> * gates)
{
    if (rand () % 2) // does nothing
        return;
    else if (rand() % 2) // adds a gate based on entropy
    {
        unsigned int control_bit = BitEntropy::getIncorrecttBit ();
        ToffoliGate * new_gate = new ToffoliGate (control_bit);
        new_gate->setControl (rand () % 2, BitEntropy::getCorrectBit ());
        for (unsigned int i = rand () % 5; i > 0; i--)
            new_gate->setControl (rand () % 2, BitEntropy::getCorrectBit ());
        gates->push_back (new_gate);
    }
}



bool GAMultiplier::operator < (const GAMultiplier& other) const 
{
    if (this->correct_answers.size () < other.correct_answers.size ())
        return true;
    else
        return false;
}
