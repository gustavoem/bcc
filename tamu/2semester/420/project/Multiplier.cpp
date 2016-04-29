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


Multiplier::Multiplier (Multiplier& other)
{
    initGates ();
    
    for (unsigned int i = 0; i < 30; i++)
        for (unsigned int j = 0; j < other.gates[i]->size (); j++)
            this->gates[i]->push_back (new ToffoliGate (*((*(other.gates[i]))[j])));

    correct_answers = other.correct_answers;
    bit_score = other.bit_score;
    eval_reps = other.eval_reps;
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


Multiplier::Multiplier (unsigned int eval_reps, unsigned int prime1, unsigned int prime2)
{
    unsigned int input = (prime1 << 15) + prime2;
    unsigned int output = prime1 * prime2;
    std::vector< std::pair<bool, unsigned int> > control_points;
    this->eval_reps = eval_reps;
    initGates ();

    unsigned int bit_index = 0;
    while (input > 0 || output > 0)
    {
        unsigned int input_bit = input % 2;
        unsigned int output_bit = output % 2;
        if (input_bit != output_bit)
        {
            ToffoliGate * gate = new ToffoliGate (bit_index);
            gates[bit_index]->push_back (gate);
            control_points.push_back (std::make_pair (input_bit, bit_index));
        }
        input >>= 1;
        output >>= 1;
        bit_index++;
    }

    // this is not n^3, don't worry (its #gates^2)
    // but remember that #gates here is less than 30
    for (unsigned int i = 0; i < 30; i++)
        for (unsigned int j = 0; j < gates[i]->size (); j++)
            for (unsigned int k = 0; k < control_points.size (); k++)
                if (rand () % 2)
                    (*gates[i])[j]->setControl (control_points[k].first, control_points[k].second);

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


