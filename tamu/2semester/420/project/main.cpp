#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main ()
{
    GeneticAlgorithm ga (100);
    ga.bestMultiplier ();
    return 0;
}
