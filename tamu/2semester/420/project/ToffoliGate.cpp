#include "ToffoliGate.h"
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>

ToffoliGate::ToffoliGate (unsigned int domain_size, unsigned int controlled_bit)
{
    this->domain_size = domain_size;
    this->controlled_bit = controlled_bit;
    gate = 0;
}


ToffoliGate::~ToffoliGate ()
{
    return;
}


void ToffoliGate::setControl (bool open, unsigned int index)
{
    // if open (true) then bit value should be one
    // if !open (false) then bit value should be 2
    std::cout << "setting " << open << " on " << index << std::endl;
    gate += (2 - open) * pow (3, index); 
    std::cout << "   me: " << toString () << std::endl;
}


void ToffoliGate::removeControl (unsigned int index)
{
    unsigned int index_help = pow (3, index);
    unsigned int divided_gate = gate / index_help;
    
    gate -= (divided_gate % 3) * index_help;
}


unsigned int ToffoliGate::applyGate (unsigned int test_number, unsigned int apply_number)
{
    bool should_change = true;
    unsigned int gate_copy = gate;
    unsigned int result = apply_number;
    
    std::cout << "applying gate: " << toString () << std::endl;
    std::cout << "test, apply: " << test_number << ", "<< apply_number << std::endl;
    
    while (test_number > 0 || gate_copy > 0)
    {
        unsigned int gate_bit = gate_copy % 3;
        unsigned int number_bit = test_number % 2; 
        
        std::cout << "  gate_bit, number_bit: " << gate_bit << ", " << number_bit << std::endl;

        if (gate_bit)
            if (number_bit != (2 - gate_bit))
            {
                should_change = false;
                break;
            }
        
       gate_copy /= 3;
       test_number /= 2;
    }
    
    if (should_change)
    {
        result ^= (1 << controlled_bit);
    }
    
    std::cout << "result: " << result << std::endl;
    return result;
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
    std::string s = ss.str ();
    std::reverse (s.begin (), s.end ());
    
    std::stringstream controlled_bit_part;
    controlled_bit_part << ": " << controlled_bit;
    s.append (controlled_bit_part.str ());
    return s;
}
