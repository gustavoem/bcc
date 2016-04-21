#include "Multiplier.h"
#include <string>
#include <sstream>
#include <iostream>

Multiplier::Multiplier ()
{
    initGates ();
}


Multiplier::Multiplier (std::vector<ToffoliGate *> new_gates)
{
    initGates ();
    for (unsigned int i = 0; i < new_gates.size (); i++)
        addGate (new_gates[i]);
}


void Multiplier::initGates ()
{
    for (unsigned int i = 0; i < 30; i++)
        gates[i] = new std::vector<ToffoliGate *> ();
}


Multiplier::~Multiplier ()
{
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> * column = gates[i];
        for (unsigned int j = 0; j < column->size (); j++)
            delete (*column)[j];
        delete column;
    }
}


unsigned int Multiplier::multiply (unsigned int number)
{
    unsigned int result = number;
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> * column = gates[i];
        for (unsigned int j = 0; j < column->size (); j++)
            result = (*column)[j]->applyGate (number, result);
    }
    return result;
}


void Multiplier::addGate (ToffoliGate * gate)
{
    unsigned int column_index = gate->getControlBit ();
    if (column_index > 29)
        return;

    gates[column_index]->push_back (gate);
}


std::map<unsigned int, std::vector<ToffoliGate *> *> Multiplier::getGates ()
{
    return gates;
}


std::string Multiplier::toString ()
{
    std::stringstream ss;
    ss << "--------------" << std::endl << "Multiplier: " << this << std::endl;
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector <ToffoliGate *> * column = gates[i];
        for (unsigned int j = 0; j < column->size (); j++)
            ss << std::endl << (*column)[j]->toString ();
    }
    ss << std::endl << "--------------";
    return ss.str ();
}
