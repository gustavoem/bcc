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


std::vector<ToffoliGate *> HCMultiplier::getRandomNeighbour ()
{
    std::vector<ToffoliGate *> new_gates;
    return new_gates;
}


bool HCMultiplier::operator < (const HCMultiplier& other) const
{
    return this->bit_score < other.bit_score;
}
