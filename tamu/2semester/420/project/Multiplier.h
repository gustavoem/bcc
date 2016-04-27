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
#include <set>
#include "PrimeList.h"
#include "BitEntropy.h"

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
        
       
        // Set of all correct combination of primes that this gate is guaranteed to
        // multilpy correctly
        // 
        std::set<std::pair<unsigned int, unsigned int> > correct_answers;

        
        // This score is the number pairs of bits of output and expected output
        // When all bits of a multiplication are correct the score is summed by 30 * 2
        // When n < 30 bits are correct the score is summed by n
        //
        unsigned int bit_score;

       
        // Stores the number of primes that should be tested to evaluate this multiplier
        //
        unsigned int eval_reps;


        // Determines the fitness of this multiplier
        // 
        void eval ();

        
    public:

        // Default constructor
        //
        Multiplier (unsigned int);
        

        // Copy constructor
        //
        Multiplier (Multiplier&);


        // Constructor with a vector of gates
        //
        Multiplier (unsigned int, std::vector<ToffoliGate *>);


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


        // Get a vector of copies of all gates
        // 
        std::vector<ToffoliGate *> getGatesCopy ();

        
        // Returns all the guaranteed inputs that this multiplier can succsesfully 
        // multiply
        //
        std::set<std::pair<unsigned int, unsigned int> > getCorrectAnswers ();


        // Score getters
        //
        unsigned int getFitness ();
        unsigned int getBitFitness ();


        // Returns string representation
        //
        std::string toString ();
};

#endif
