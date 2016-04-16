#include "ToffoliGate.h"
#include <sstream>
#include <iostream>

ToffoliGate::ToffoliGate (unsigned int domain_size)
{
    this->domain_size = domain_size;
    gate = 0;
}


ToffoliGate::~ToffoliGate ()
{
    return;
}


std::string ToffoliGate::toString ()
{
    std::stringstream ss;
    unsigned int gate_copy = gate;
    char map[3] = {'X', '1', '0'};

    for (unsigned int i = 0; i < domain_size; i++)
    {
        ss << map[gate_copy % 3];
        gate_copy /= 3;
    }
    return ss.str ();
}
