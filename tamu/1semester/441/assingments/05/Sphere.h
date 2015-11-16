#ifndef SPHERE_H_
#define SPHERE_H_

#include "global.h"
#include "Object.h"

class Sphere : public Object
{

private:

    // Stores the size of the Sphere
    //
    double size;

public:

    // Default constructor
    //
    Sphere (R3Vector, double, Color, Material);


    // Default destructor
    //
    virtual ~Sphere ();


    // Intersects the shere with a ray
    //
    virtual pair<Color, R3Vector> * intersect (R3Vector, R3Vector);


    // Returns material of the sphere
    //
    virtual Material getMaterial ();


    // Returns the normal R3Vector from a given point of the sphere. If the point its not
    // from the sphere, the method will return a R3Vector N which is the normal R3Vector of
    // the given point p in a sphere with same center and with radius equals to 
    // |p - center|
    //
    virtual R3Vector getNormal (R3Vector);

};

#endif