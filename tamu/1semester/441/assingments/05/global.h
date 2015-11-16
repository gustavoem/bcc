#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <math.h>

using namespace std;

struct Vector 
{
	double x;
	double y;
	double z;
};


struct Color
{
	double r;
	double g;
	double b;
};

	
struct Material
{
	double k_a;
	double k_d;
	double k_s;
};

void normalize (Vector *);

#endif