#ifndef SPHERE_H_
#define SPHERE_H_

#include "global.h"

class Sphere
{

private:

	// Stores the location of the Sphere
	//
	Vertex center;


	// Stores the size of the Sphere edges
	//
	double size;

public:

	// Default constructor
	//
	Sphere (Vertex, double);


	// Default destructor
	//
	virtual ~Sphere ();
};

#endif