#ifndef OBJECT_H_
#define OBJECT_H_

#include "global.h"

class Object
{

protected:

    // Stores the location of the material
    //
    Vector center;


    // Stores the color of the material
    // 
    Color color;


    // Stores the material of the material
    // 
    Material material;

public:

    // Default constructor
    //
    Object (Vector, Color, Material);


    // Default destructor
    //
    virtual ~Object ();


    // Intersects the shere with a ray
    //
    virtual pair<Color, Vector> * intersect (Vector, Vector) = 0;


    // Returns material of the sphere
    //
    virtual Material getMaterial () = 0;


    // Returns the normal vector from a given point of the sphere. If the point its not
    // from the sphere, the method will return a vector N which is the normal vector of
    // the given point p in a sphere with same center and with radius equals to 
    // |p - center|
    //
    virtual Vector getNormal (Vector) = 0;

};

#endif