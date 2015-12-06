#ifndef CATMULLROM_H
#define CATMULLROM_H

#include "posture.h"
#include "vector.h"

static class CatmullRom
{
public:

	// Makes the interpolation between a and b at time t
	//
	static Posture interpolate (Posture a, Posture b, float t);


	// Returns a posture that is the reflection of b in relation to a
	//
	static Posture reflectPosture (Posture a, Posture b);
};

#endif