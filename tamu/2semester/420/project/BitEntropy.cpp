#include "BitEntropy.h"

unsigned int BitEntropy::wrong_bit_occurrences[30];


bool BitEntropy::EntropyComparator::operator () 
    (std::pair<unsigned int, unsigned int> lhs, 
     std::pair<unsigned int, unsigned int> rhs) const 
{
    if (lhs.first < rhs.first)
        return true;
    else if (lhs.first == rhs.first && lhs.second < rhs.second)
        return true;
    else
        return false;
}

void BitEntropy::initBitEntropy ()
{
    for (unsigned int i = 0; i < 30; i++)
        wrong_bit_occurrences[i] = 0;
}


void BitEntropy::addBitOccurrence (unsigned int bit_index, bool correct)
{
    if (!correct)
        wrong_bit_occurrences[bit_index]++;
}


unsigned int BitEntropy::getHighEntropyBit ()
{
    std::set<std::pair<unsigned int, unsigned int>, EntropyComparator> entropies;
    for (unsigned int i = 0; i < 30; i++) 
        entropies.insert (std::make_pair (wrong_bit_occurrences[i], i));

    std::set<std::pair<unsigned int, 
        unsigned int> >::reverse_iterator it (entropies.rbegin ());
    advance (it, rand () % 5);
    return it->second;
}


unsigned int BitEntropy::getLowEntropyBit ()
{
    std::set<std::pair<unsigned int, unsigned int>, EntropyComparator> entropies;
    for (unsigned int i = 0; i < 30; i++) 
        entropies.insert (std::make_pair (wrong_bit_occurrences[i], i));

    std::set<std::pair<unsigned int, unsigned int> >::iterator it (entropies.begin ());
    advance (it, rand () % 10);
    return it->second;
}


std::string BitEntropy::toString ()
{
    std::stringstream ss;
    ss << "|";
    for (unsigned int i = 0; i < 30; i++)
        ss << wrong_bit_occurrences[i] << "|";
    ss << std::endl;
    return ss.str ();
}
