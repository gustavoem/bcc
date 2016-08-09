#include <stdio.h>
#include "DIGRAPHlists.h"

int main () {
	Digraph d;
	d = DIGRAPHinit (6);
	DIGRAPHinsertA (d, 1, 2);
	DIGRAPHinsertA (d, 2, 0);
	DIGRAPHinsertA (d, 2, 3);
	DIGRAPHshow (d);
	DIGRAPHremoveA (d, 2, 0);
	DIGRAPHshow (d);
	DIGRAPHremoveA (d, 1, 2);
	DIGRAPHshow (d);
	DIGRAPHremoveA (d, 2, 3);
	DIGRAPHshow (d);
	return 0;
}