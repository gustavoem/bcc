#include <iostream>
#include <iomanip>

#include "ToffoliGate.h"
#include "Multiplier.h"

using namespace std;

int main ()
{
    ToffoliGate tf_gate (5, 2);
    ToffoliGate tf_gate1 (5, 3);
    
    tf_gate.setControl (true, 1);
    tf_gate.setControl (false, 2);
    cout << tf_gate.toString () << endl;

    tf_gate1.setControl (true, 3);
    tf_gate1.setControl (false, 2);
    cout << tf_gate1.toString () << endl;

    Multiplier mp;
    mp.addGate (&tf_gate);
    mp.addGate (&tf_gate1);

    cout << 10 << endl;
    cout << mp.multiply (10) << endl;
    cout << 3 << endl;
    cout << mp.multiply (3) << endl;
    cout << 9 << endl;
    cout << mp.multiply (9) << endl;
    return 0;
}
