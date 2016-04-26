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

void showUsage ();

int main (int argc, char * argv[])
{
    if (argc < 2)
    {
        showUsage ();
        return 0;
    }

    if (string (argv[1]) == "-l")
    {
        unsigned int nof_beams = 0;
        if (argc < 3)
        {
            showUsage ();
            return 0;
        }
        else
        {
            nof_beams = atoi (argv[2]);
        }
        LocalBeam hc (nof_beams);
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


void showUsage ()
{
    cout << "Usage is -l <number of beams> for local beam search and -g for genetic algorithm" << endl;
}