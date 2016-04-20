#include "ToffoliGate.h"
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>

ToffoliGate::ToffoliGate (unsigned int controlled_bit)
{
    this->controlled_bit = controlled_bit;
    gate[0] = 0;
    gate[1] = 0;
}


ToffoliGate::ToffoliGate (ToffoliGate& original)
{
    this->gate[0] = original.gate[0];
    this->gate[1] = original.gate[1];
    this->controlled_bit = original.controlled_bit;
}


ToffoliGate::~ToffoliGate ()
{
    return;
}


bool ToffoliGate::operator < (const ToffoliGate& other) const
{
    return controlled_bit < other.controlled_bit;
}


void ToffoliGate::setControl (bool open, unsigned int index)
{
    // if open (true) then bit value should be one
    // if !open (false) then bit value should be 2
    // std::cout << "setting " << open << " on " << index << std::endl;
    // gate += (2 - open) * pow (3, index); 
    
    unsigned int half = index > 14;
    unsigned int gate_bit = (index % 15) * 2;
    
    // clean two bits
    unsigned int clean_mask = ~(3 << gate_bit);
    unsigned int set_mask = ((2 - open) << gate_bit);
    gate[half] &= clean_mask;
    gate[half] |= set_mask;

    // std::cout << "   me: " << toString () << std::endl;
    // std::cout << "after setting: " << gate[1] << "|" << gate[0] << std::endl;
}


void ToffoliGate::removeControl (unsigned int index)
{
    // unsigned int index_help = pow (3, index);
    // unsigned int divided_gate = gate / index_help;
    // gate -= (divided_gate % 3) * index_help;
    unsigned int half = index > 14;
    unsigned int gate_bit = (index - (half * 15)) * 2;
    
    // clean two bits
    unsigned int clean_mask = ~(3 << gate_bit);
    gate[half] &= clean_mask;
}


unsigned int ToffoliGate::applyGate (unsigned int test_number, unsigned int apply_number)
{
    bool should_change = true;
    unsigned int result = apply_number;
    
    // std::cout << "applying gate: " << toString () << std::endl;
    // std::cout << "test, apply: " << test_number << ", "<< apply_number << std::endl;
    
    for (unsigned int i = 0; i < 2; i++)
    {
        unsigned int gate_copy = gate[i];
        for (unsigned int j = 0; j < 15; j++)
        {
            unsigned int gate_bit = gate_copy & 3;
            unsigned int number_bit = test_number % 2; 
        
            // std::cout << "  gate_bit, number_bit: " << gate_bit << ", " << number_bit << std::endl;

            if (gate_bit)
                if (number_bit != (2 - gate_bit))
                {
                    should_change = false;
                    break;
                }
        
            gate_copy /= 4;
            test_number /= 2;
        }
    }
    
    if (should_change)
    {
        result ^= (1 << controlled_bit);
    }
    
    // std::cout << "result: " << result << std::endl;
    return result;
}


unsigned int ToffoliGate::getControlBit ()
{
    return this->controlled_bit;
}


std::string ToffoliGate::toString ()
{
    std::stringstream ss;
    char map[3] = {'X', '1', '0'};

    for (unsigned int i = 0; i < 30; i++)
    {
        unsigned int half = i > 14;
        unsigned int gate_bit = (i % 15) * 2;
        unsigned int bit_content = (gate[half] >> gate_bit) & 3;
        ss << map[bit_content];
    }

    std::string s = ss.str ();
    std::reverse (s.begin (), s.end ());
    
    std::stringstream controlled_bit_part;
    controlled_bit_part << ": " << controlled_bit;
    s.append (controlled_bit_part.str ());
    return s;
}
