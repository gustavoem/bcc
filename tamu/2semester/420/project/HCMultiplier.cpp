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
    if (new_gates->size () > MAX_GATES)
    {
        if (rand () % 2)
            addRandomControlPoint (new_gates);
        else
            removeRandomGate (new_gates);
        return;
    }

    unsigned int i = rand () % 90;
    if (i > 30)
        i = BitEntropy::getHighEntropyBit ();

    ToffoliGate * new_gate = new ToffoliGate (i);
    new_gates->push_back (new_gate);
}


void HCMultiplier::removeRandomGate (std::vector<ToffoliGate *> * new_gates)
{
    if (new_gates->size () == 0)
        addRandomGate (new_gates);

    unsigned i = rand () % new_gates->size ();
    new_gates->erase (new_gates->begin () + i);
}


void HCMultiplier::addRandomControlPoint (std::vector<ToffoliGate *> * new_gates)
{   
    if (new_gates->size () == 0)
        addRandomGate (new_gates);

    unsigned int i = rand () % new_gates->size ();
    (*new_gates)[i]->setControl (rand () % 2, BitEntropy::getLowEntropyBit ());
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
    
    unsigned int branch = rand () % 5;
    if (branch < 3)
        addRandomGate (&new_gates);
    else if (branch == 3)
        addRandomControlPoint (&new_gates);
    else
        removeRandomGate (&new_gates);

    return new_gates;
}


bool HCMultiplier::operator < (const HCMultiplier& other) const
{
    // std::cout << "Comparing " << this << " to " << &other << std::endl;
    // if (this->correct_answers.size () < other.correct_answers.size ())
        // return true;
    if (
        this->bit_score + 60 * this->correct_answers.size () < other.bit_score + 60 * other.correct_answers.size ())
        return true;
    else
        return false;
}
