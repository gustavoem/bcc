// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#include "HCMultiplier.h"

HCMultiplier::HCMultiplier (unsigned int eval_reps) : Multiplier (eval_reps) 
{
    return;
}


HCMultiplier::HCMultiplier (unsigned int eval_reps, std::vector<ToffoliGate *> gates) :
    Multiplier (eval_reps, gates)
{
    return;
}


HCMultiplier::~HCMultiplier ()
{
    return;
}


void HCMultiplier::addRandomGate (std::vector<ToffoliGate *> * new_gates)
{
    unsigned int i;
    if (rand () % 3)
        i = BitEntropy::getHighEntropyBit ();
    else
        i = rand () % 30;

    ToffoliGate * new_gate = new ToffoliGate (i);
    new_gates->push_back (new_gate);
}


void HCMultiplier::addRandomControlPoint (std::vector<ToffoliGate *> * new_gates)
{
    unsigned int i;
    if (rand () % 3)
        i = BitEntropy::getHighEntropyBit ();
    else
        i = rand () % 30;
    
    std::vector<ToffoliGate *> * column = gates[i];
    if (column->size () != 0)
    {
        unsigned int j;
        j = BitEntropy::getLowEntropyBit ();
        (*column)[j]->setControl (rand () % 2, j);
    } 
}


std::vector<ToffoliGate *> HCMultiplier::getRandomNeighbour ()
{
    std::vector<ToffoliGate *> new_gates;
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> * column = gates[i];
        for (unsigned int j = 0; j < column->size (); j++)
            new_gates.push_back (new ToffoliGate (*(*column)[j]));
    }

    if (rand () % 2)
        addRandomGate (&new_gates);
    else
        addRandomControlPoint (&new_gates);

    return new_gates;
}


bool HCMultiplier::operator < (const HCMultiplier& other) const
{
    return this->bit_score < other.bit_score;
}
