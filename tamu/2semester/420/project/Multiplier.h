// Author: Gustavo Estrela de Matos
// Date: April 2016
//
//

#ifndef MULTIPLIER_H_
#define MULTIPLIER_H_

#include "ToffoliGate.h"
#include <vector>
#include <string>
#include <map>

class Multiplier
{
    private:

        // Starts the map of gates
        //
        void initGates ();
    
    protected:

        // Stores a list of toffoli gates organized by column
        //
        std::map <unsigned int, std::vector<ToffoliGate *> *> gates;

    public:

        // Default constructor
        //
        Multiplier ();


        // Constructor with a vector of gates
        //
        Multiplier (std::vector<ToffoliGate *>);

        // Default destructor
        //
        virtual ~Multiplier ();


        // Applies the series of toffoli gates to the parameter
        //
        unsigned int multiply (unsigned int);


        // Add a toffoli gate
        //
        void addGate (ToffoliGate *);


        // Get gates in format of a map
        //
        std::map<unsigned int, std::vector<ToffoliGate *> *> getGates ();


        // Returns string representation
        //
        std::string toString ();

};

#endif
