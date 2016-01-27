// Gustavo Estrela de Matos
// CSCE 420-500
// Due: February 1, 2016 (or whatever the due date is)
// hw1pr1.cpp
//

#include <stdstream>

int main ()
{
    unsigned int n, m;
    unsigned int ** room_floor;
    
    scanf ("%d %d", n, m);
    room_floor = new unsigned int * [n];
    for (unsigned int i = 0; i < n; i++)
        room_floor[i] = new unsigned int[m];

    
    for (unsigned int i = 0; i < n; i++)
        delete room_floor[i];
    delete room_floor;
    return;
}

