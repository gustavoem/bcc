#ifndef CUBE_H_
#define CUBE_H_

#include "global.h"

class Cube
{

private:

	// Stores the location of the cube
	//
	Vertex center;


	// Stores the size of the cube edges
	//
	double size;

public:

	// Default constructor
	//
	Cube (Vertex, double);


	// Default destructor
	//
	virtual ~Cube ();
};

#endif