#include "Multiplier.h"
#include <string>
#include <sstream>
#include <iostream>

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


std::string Multiplier::toString ()
{
    std::stringstream ss;
    ss << "--------------" << std::endl << "Multiplier: " << this << std::endl;
    for (unsigned int i = 0; i < gates.size (); i++)
    {
        ss << std::endl << gates[i]->toString ();
    }
    ss << std::endl << "--------------";
    return ss.str ();
}
