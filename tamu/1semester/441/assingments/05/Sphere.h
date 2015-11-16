#ifndef SPHERE_H_
#define SPHERE_H_

#include "global.h"

class Sphere
{

private:

    // Stores the location of the Sphere
    //
    Vector center;


    // Stores the size of the Sphere edges
    //
    double size;



    // Stores the color of the sphere
    // 
    Color color;


    // Stores the material of the sphere
    // 
    Material material;

public:

    // Default constructor
    //
    Sphere (Vector, double, Color, Material);


    // Default destructor
    //
    virtual ~Sphere ();


    // Intersects the shere with a ray
    //
    pair<Color, Vector> * intersect (Vector, Vector);


    // Returns material of the sphere
    //
    Material getMaterial ();


    // Returns the normal vector from a given point of the sphere. If the point its not
    // from the sphere, the method will return a vector N which is the normal vector of
    // the given point p in a sphere with same center and with radius equals to 
    // |p - center|
    //
    Vector getNormal (Vector);

};

#endif