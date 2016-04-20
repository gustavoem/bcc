#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main ()
{
    ToffoliGate * a = new ToffoliGate (1);
    ToffoliGate * c = new ToffoliGate (12);
    ToffoliGate * b = new ToffoliGate (10);
    vector<ToffoliGate *> v;
    v.push_back (a);
    v.push_back (b);
    v.push_back (c);

    for (std::vector<ToffoliGate *>::iterator it = v.begin (); it != v.end (); ++it)
        std::cout << (*it)->toString () << endl;

    GeneticAlgorithm ga (300);
    ga.bestMultiplier ();
    return 0;
}
