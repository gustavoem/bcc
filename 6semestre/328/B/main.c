#include <stdio.h>
#include "DIGRAPHlists.h"

int main () {
	Digraph d;
	d = DIGRAPHinit (5);
	DIGRAPHshow (d);
	return 0;
}