// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef TOFFOLI_GATE_H_
#define TOFFOLI_GATE_H_

#include <string>

class ToffoliGate
{
    
    private:

        // Stores the index of the highest bit that this toffoli gate applies to
        //
        unsigned int domain_size;
        

        // Stores the toffoli gate itself
        // We use a base_3 number to represent a toffoli gate here, where:
        // - 0 represents don't care
        // - 1 represents regular control bit (contributes if bit is one)
        // - 2 represents inverted control bit (contributes if bit is zero)
        //
        unsigned int gate;


        // Stores the output bit index
        //
        unsigned int controlled_bit;


    public:
        
        // Default constructor
        //
        ToffoliGate (unsigned int, unsigned int);


        // Default destructor
        //
        virtual ~ToffoliGate ();
    

        // Sets a closed or open (first argument) control on (second argument)-th bit
        // Does nothing if arguments are invalid
        //
        void setControl (bool, unsigned int);


        // Removes a control point from the gate
        //
        void removeControl (unsigned int);

        
        // Tests the gate agains the first parameter and applies it to the second parameter
        //
        unsigned int applyGate (unsigned int, unsigned int);

        // Returns string representation of the gate
        //
        std::string toString ();
};

#endif
