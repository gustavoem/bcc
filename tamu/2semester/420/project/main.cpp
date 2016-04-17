#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"

using namespace std;

int main ()
{
    ToffoliGate tf_gate (5, 2);
    unsigned int number = 15;

    tf_gate.setControl (true, 0);
    tf_gate.setControl (true, 2);
    tf_gate.setControl (false, 4);
    cout << tf_gate.toString() << endl;

    cout << number << endl;
    cout << tf_gate.applyGate (number) << endl;
    
    return 0;
}
