#include "BitEntropy.h"

unsigned int BitEntropy::wrong_bit_occurrences[30];

void BitEntropy::initBitEntropy ()
{
    for (unsigned int i = 0; i < 30; i++)
        wrong_bit_occurrences[i] = 0;
}


void BitEntropy::addBitOccurence (unsigned int bit_index, bool correct)
{
    if (!correct)
        wrong_bit_occurrences[bit_index]++;
}


unsigned int BitEntropy::getHighEntropyBit ()
{
    std::set<unsigned int> indexes;
    for (unsigned int i = 0; i < 30; i++)
    {
        std::set<unsigned int>::iterator worst_best (indexes.end ());
        worst_best--;
        if (!(worst_best == indexes.begin ()) && 
            wrong_bit_occurrences[*worst_best] < wrong_bit_occurrences[i])
            indexes.insert (i);
        
        worst_best = indexes.end ();
        worst_best--;
        if (indexes.size () > 5)
            indexes.erase (worst_best);
    }
    std::set<unsigned int>::iterator it (indexes.begin ());
    advance (it, rand () % 5);
    return *it;
}


unsigned int BitEntropy::getLowEntropyBit ()
{
    return 0;
}
