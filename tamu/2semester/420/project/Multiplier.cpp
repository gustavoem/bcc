#include "Multiplier.h"
#include <sstream>
#include <iostream>

Multiplier::Multiplier (unsigned int eval_reps)
{
    this->eval_reps = eval_reps;
    if (eval_reps == 0)
        eval_reps = g_number_of_primes;

    bit_score = 0;
    initGates ();
}


Multiplier::Multiplier (unsigned int eval_reps, std::vector<ToffoliGate *> new_gates)
{
    initGates ();
    for (unsigned int i = 0; i < new_gates.size (); i++)
        addGate (new_gates[i]);

    this->eval_reps = eval_reps;
    if (eval_reps == 0)
        eval_reps = g_number_of_primes;
    eval ();

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


void Multiplier::eval ()
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
            bool bit_match = ((output >> i) & 1) == ((expected_output >> i) & 1);
            if (bit_match)
                bit_score++;
            
            BitEntropy::addBitOccurrence (i, bit_match);
        }
        if (output == expected_output)
            correct_answers.insert (std::make_pair (prime1, prime2));
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


std::vector<ToffoliGate *> Multiplier::getGatesCopy ()
{
    std::vector<ToffoliGate *> allGates;
    for (unsigned int i = 0; i < 30; i++)
    {
        std::vector<ToffoliGate *> * column = gates[i];
        for (unsigned int j = 0; j < column->size (); j++)
        {
            ToffoliGate * new_gate = new ToffoliGate (*(*column)[j]);
            allGates.push_back (new_gate);
        }
    }
    return allGates;
}


std::set<std::pair<unsigned int, unsigned int> > Multiplier::getCorrectAnswers ()
{
    return this->correct_answers;
}


unsigned int Multiplier::getFitness ()
{
    return this->correct_answers.size ();
}


unsigned int Multiplier::getBitFitness ()
{
    return this->bit_score;
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


