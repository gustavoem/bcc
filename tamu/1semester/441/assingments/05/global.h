#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

struct R3Vector 
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
    unsigned int n;
};

void normalize (R3Vector *);

#endif