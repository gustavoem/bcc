#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"
#include "GAMultiplier.h"

using namespace std;

int main ()
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

    return 0;
}
