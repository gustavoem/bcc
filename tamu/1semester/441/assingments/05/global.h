/*
    Author: Gustavo Estrela de Matos
    Date: 11/18/15
*/
    
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

class Object;

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
    double k_r;
    
    Material ()
    {
        k_a = 0;
        k_d = 0;
        k_s = 0;
        n = 0;
    }

    Material (double a, double d, double s, unsigned int na, double r)
    {
        k_a = a;
        k_d = d;
        k_s = s;
        n = na;
        k_r = r;
    }
};

struct Intersection
{
    Color color;
    R3Vector point;
    Object * object;
};

void normalize (R3Vector *);

double norm (R3Vector);

double prod (R3Vector, R3Vector);

#endif