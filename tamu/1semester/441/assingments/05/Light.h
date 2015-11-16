#ifndef LIGHT_H_
#define LIGHT_H_

#include "global.h"

class Light
{

private:

    // Stores the location of the Light
    //
    Vector center;


    // Stores the color of the light
    // 
    Color intensity;

public:

    // Default constructor
    //
    Light (Vector, Color);


    // Default destructor
    //
    virtual ~Light ();


    // Returns intensity of the light
    //
    Color getIntensity ();
};

#endif