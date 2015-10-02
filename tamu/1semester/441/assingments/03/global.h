#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <utility> // pair
#include <vector>  // vector
#include <algorithm> // sort
#include <iostream>

#define ImageW 400
#define ImageH 400

using namespace std;

struct Edge 
{
    unsigned int max_y;
    double current_x;
    double x_increment;
};

#endif