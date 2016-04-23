// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef BIT_ENTROPY_H_
#define BIT_ENTROPY_H_

#include <set>
#include <stdlib.h>

class BitEntropy
{
    
    private:

        // Number of times that we looked at bit i and it was wrong comparing
        // multiplication output and expected output
        //
        static unsigned int wrong_bit_occurrences[30];


    public:
       

        // Starts namespaces variables
        //
        static void initBitEntropy ();


        // Updates entropy and mapping with a new bit occurence
        //
        static void addBitOccurence (unsigned int, bool);


        // Returns the index of a bit with high entropy
        //
        unsigned int getHighEntropyBit ();


        // Returns the index of a bit with low entropy
        //
        unsigned int getLowEntropyBit ();
};

#endif
