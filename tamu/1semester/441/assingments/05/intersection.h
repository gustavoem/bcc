#ifndef INTERSECTION_H_
#define INTERSECTION_H_

class Object;

struct Intersection 
{
    Color color;
    R3Vector point;
    Object * object;
};

#endif