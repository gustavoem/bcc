#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main ()
{
    ToffoliGate * a = new ToffoliGate (1);
    ToffoliGate * b = new ToffoliGate (10);
    ToffoliGate * c = new ToffoliGate (12);
    set<ToffoliGate *> v;
    v.insert (a);
    v.insert (b);
    v.insert (c);

    for (std::set<ToffoliGate *>::iterator it = v.begin (); it != v.end (); ++it)
        std::cout << (*it)->toString () << endl;

    GeneticAlgorithm ga (300);
    ga.bestMultiplier ();
    return 0;
}
