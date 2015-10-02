#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <utility> // pair
#include <vector>  // vector
#include <algorithm> // sort
#include <iostream>
#include <cmath>

#define ImageW 400
#define ImageH 400

using namespace std;

struct Point
{
	unsigned int x;
	unsigned int y;
	unsigned int flag;
};

struct Edge 
{
    unsigned int max_y;
    double current_x;
    double x_increment;
};

// Color struct
//
struct color {
    float r, g, b;      // Color (R,G,B values)
};


#endif