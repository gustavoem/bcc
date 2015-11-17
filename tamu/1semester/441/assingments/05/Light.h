#ifndef LIGHT_H_
#define LIGHT_H_

#include "global.h"
#include "Sphere.h"

class Light : public Sphere
{

private:


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
    Color getDiffuseLight (R3Vector, R3Vector, double);


    // Returns the specular light from this source to a point p0 with normal N being
    // looked from E
    //
    Color getSpecularLight (R3Vector, R3Vector, R3Vector, double, double);


    // Returns true if object is a Light
    //
    virtual bool isLight ();
};

#endif