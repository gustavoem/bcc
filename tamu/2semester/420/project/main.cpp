#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main ()
{
    for (std::vector<ToffoliGate *>::iterator it = v.begin (); it != v.end (); ++it)
        std::cout << (*it)->toString () << endl;

    GeneticAlgorithm ga (300);
    ga.bestMultiplier ();
    return 0;
}
