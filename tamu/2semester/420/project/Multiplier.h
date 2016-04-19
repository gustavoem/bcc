// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef MULTIPLIER_H_
#define MULTIPLIER_H_

#include "ToffoliGate.h"
#include <vector>
#include <string>

class Multiplier
{
    private:
    
    protected:

        // Stores a list of toffoli gates
        //
        std::vector<ToffoliGate *> gates;


    public:

        // Default constructor
        //
        Multiplier ();


        // Default destructor
        //
        virtual ~Multiplier ();


        // Applies the series of toffoli gates to the parameter
        //
        unsigned int multiply (unsigned int);


        // Add a toffoli gate
        //
        void addGate (ToffoliGate *);


        // Returns string representation
        //
        std::string toString ();
};

#endif
