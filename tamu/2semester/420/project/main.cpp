#include <iostream>
#include <iomanip>
#include <string>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"
#include "GAMultiplier.h"
#include "LocalBeam.h"
#include "LBMultiplier.h"

using namespace std;

int main (int argc, char * argv[])
{
    if (argc < 2)
    {
        cout << "Usage is -l for local beam search and -g for genetic algorithm" << endl;
        return 0;
    }

    if (string (argv[1]) == "-l")
    {
        LocalBeam hc;
        LBMultiplier * multiplier = hc.bestMultiplier (); 
    }
    else if (string (argv[1]) == "-g")
    {
        GeneticAlgorithm ga (300);
        GAMultiplier * multiplier = ga.bestMultiplier ();
        cout << "Solution: " << endl;
        cout << multiplier->toString () << endl;
        set<pair<unsigned int, unsigned int> > correct_cases = 
            multiplier->getCorrectAnswers ();

        for (set<pair<unsigned int, unsigned int> >::iterator it = correct_cases.begin ();
                it != correct_cases.end (); ++it)
            cout << it->first << " x " << it->second << endl;
    }
    return 0;
}
