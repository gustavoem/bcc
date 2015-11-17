#ifndef OBJECT_H_
#define OBJECT_H_

#include "global.h"

class Object
{

protected:

    // Stores the location of the material
    //
    R3Vector center;


    // Stores the color of the material
    // 
    Color color;


    // Stores the material of the material
    // 
    Material material;

public:

    // Default constructor
    //
    Object (R3Vector, Color, Material);


    // Default destructor
    //
    virtual ~Object ();


    // Intersects the shere with a ray
    //
    virtual Intersection * intersect (R3Vector, R3Vector) = 0;


    // Returns material of the sphere
    //
    virtual Material getMaterial () = 0;


    // Returns the normal R3Vector from a given point of the sphere. If the point its not
    // from the sphere, the method will return a R3Vector N which is the normal R3Vector of
    // the given point p in a sphere with same center and with radius equals to 
    // |p - center|
    //
    virtual R3Vector getNormal (R3Vector) = 0;


    // Returns true if object is a Light
    //
    virtual bool isLight ();


    // Returns the center of the object
    //
    R3Vector getCenter ();


    // Returns the object color
    //
    Color getColor ();
};

#endif