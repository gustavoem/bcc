#include <iostream>

#include "ToffoliGate.h"

using namespace std;

int main ()
{
    ToffoliGate tf_gate (5);
    cout << tf_gate.toString() << endl;

    return 0;
}
