#include "Multiplier.h"


Multiplier::Multiplier ()
{
    return;
}


Multiplier::~Multiplier ()
{
    return;
}


unsigned int Multiplier::multiply (unsigned int number)
{
    unsigned int result = number;
    
    for (unsigned int i = 0; i < gates.size (); i++)
    {
        result = gates[i]->applyGate (number, result);
    }

    return result;
}


void Multiplier::addGate (ToffoliGate * gate)
{
    gates.push_back (gate);
}
