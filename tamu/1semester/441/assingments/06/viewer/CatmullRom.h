#ifndef CATMULLROM_H
#define CATMULLROM_H

#include "posture.h"
#include "vector.h"

//using namespace std;

struct ControlPoint
{
	unsigned int frame;
	Posture posture;
};

class CatmullRom
{
public:

	// Makes the interpolation between a and b at time t
	//
	static Posture interpolate (Posture a, Posture b, float t);


	// Returns a posture that is the reflection of b in relation to a
	//
	static ControlPoint reflectControlPoints (ControlPoint a, ControlPoint b);
};

#endif