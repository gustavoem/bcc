#include <stdio.h>
#include "DIGRAPHmatrix.h"

int main () {
	Digraph d;
	d = DIGRAPHinit (5);
	DIGRAPHshow (d);
	return 0;
}