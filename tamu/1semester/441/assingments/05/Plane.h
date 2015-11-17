#ifndef PLANE_H_
#define PLANE_H_

#include "global.h"
#include "Object.h"

class Plane : public Object
{

private:

    // Stores the normal of the plane
    //
    R3Vector normal;

public:

    // Default constructor
    //
    Plane (R3Vector, Color, Material, R3Vector);


    // Default destructor
    //
    virtual ~Plane ();


    // Intersects the shere with a ray
    //
    virtual Intersection * intersect (R3Vector, R3Vector);


    // Returns material of the Plane
    //
    virtual Material getMaterial ();


    // Returns the normal R3Vector of the Plane.
    //
    virtual R3Vector getNormal (R3Vector);

};

#endif