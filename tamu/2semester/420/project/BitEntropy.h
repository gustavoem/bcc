// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef BIT_ENTROPY_H_
#define BIT_ENTROPY_H_

#include <set>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

class BitEntropy
{
    
    private:

        // Number of times that we looked at bit i and it was wrong comparing
        // multiplication output and expected output
        //
        static unsigned int wrong_bit_occurrences[30];
        

        struct EntropyComparator 
        {
            bool operator () (std::pair<unsigned, unsigned>, 
                    std::pair<unsigned int, unsigned int>) const;
        };

    public:
       

        // Starts namespaces variables
        //
        static void initBitEntropy ();


        // Updates entropy and mapping with a new bit occurence
        //
        static void addBitOccurrence (unsigned int, bool);


        // Returns the index of a bit with high entropy
        //
        static unsigned int getHighEntropyBit ();


        // Returns the index of a bit with low entropy
        //
        static unsigned int getLowEntropyBit ();


        // Returns a string representation of bit entropy
        //
        static std::string toString ();
};

#endif
