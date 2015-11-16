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
    Sphere (Vector, double, Color, Material);


    // Default destructor
    //
    virtual ~Sphere ();


    // Intersects the shere with a ray
    //
    virtual pair<Color, Vector> * intersect (Vector, Vector);


    // Returns material of the sphere
    //
    virtual Material getMaterial ();


    // Returns the normal vector from a given point of the sphere. If the point its not
    // from the sphere, the method will return a vector N which is the normal vector of
    // the given point p in a sphere with same center and with radius equals to 
    // |p - center|
    //
    virtual Vector getNormal (Vector);

};

#endif