#include <stdio.h>
#include "DIGRAPHmatrix.h"

int main () {
    Digraph d;
    d = DIGRAPHinit (6);
    DIGRAPHinsertA (d, 1, 2);
    DIGRAPHinsertA (d, 2, 0);
    DIGRAPHinsertA (d, 2, 3);
    printf ("Grau de saida de 2: %d \n", DIGRAPHoutdeg (d, 2));
    printf ("Grau de entrada de 2: %d \n", DIGRAPHindeg (d, 2));
    DIGRAPHshow (d);
    DIGRAPHremoveA (d, 2, 0);
    DIGRAPHshow (d);
    DIGRAPHremoveA (d, 1, 2);
    DIGRAPHshow (d);
    DIGRAPHdestroy (d);
    return 0;
}