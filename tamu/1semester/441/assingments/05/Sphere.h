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

public:

	// Default constructor
	//
	Sphere (Vector, double);


	// Default destructor
	//
	virtual ~Sphere ();


	// Intersects the shere with a ray
	//
	Color intersect (Vector);
};

#endif