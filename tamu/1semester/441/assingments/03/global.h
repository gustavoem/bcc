#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <utility> // pair
#include <vector>  // vector

#define ImageW 400
#define ImageH 400

using namespace std;

struct Edge 
{
    unsigned int max_y;
    float current_x;
    float x_increment;
};

#endif