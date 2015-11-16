#ifndef LIGHT_H_
#define LIGHT_H_

#include "global.h"

class Light
{

private:

    // Stores the location of the Light
    //
    R3Vector center;


    // Stores the color of the light
    // 
    Color intensity;

public:

    // Default constructor
    //
    Light (R3Vector, Color);


    // Default destructor
    //
    virtual ~Light ();


    // Returns intensity of the light
    //
    Color getIntensity ();


    // Returns the diffuse light from this source to a point p0 with normal N
    //
    Color getDiffuseLight (R3Vector, R3Vector);
};

#endif