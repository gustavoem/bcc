#ifndef CATMULLROM_H
#define CATMULLROM_H

#include "posture.h"
#include "vector.h"
#include <iostream>

using namespace std;

struct ControlPoint
{
	unsigned int frame;
	Posture posture;
};

class CatmullRom
{

private:
	
	// Calculate C * p in the CatmullRom algorithm
	//
	static float * calculate_Cp (float p0, float p1, float p2, float p3);


	// Calculates the interpolation of float values using CatmullRom algorithm
	//
	static float interpolate_values (float p0, float p1, float p2, float p3, float u);

public:

	// Makes the interpolation between a and b at time t
	//
	static Posture interpolate (ControlPoint p0, ControlPoint p1, ControlPoint p2, ControlPoint p3, unsigned int frame);


	// Returns a posture that is the reflection of b in relation to a
	//
	static ControlPoint reflectControlPoints (ControlPoint a, ControlPoint b);
};

#endif