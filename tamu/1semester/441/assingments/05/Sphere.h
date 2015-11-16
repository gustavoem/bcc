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


    // Stores the ambient reflection coeficient
    // 
    double k_a;

public:

    // Default constructor
    //
    Sphere (Vector, double, Color, double);


    // Default destructor
    //
    virtual ~Sphere ();


    // Intersects the shere with a ray
    //
    pair<Color, Vector> * intersect (Vector, Vector);


    // Returns the coeficient for ambient light reflection
    //
    double getAmbientCoef ();


    // Returns the coeficient for diffuse light reflection
    //
    double getDiffusetCoef ();
};

#endif