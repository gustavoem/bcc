#include "Sphere.h"

Sphere::Sphere (Vertex pos, double size)
{
	center = pos;
	this->size = size;
}

Sphere::~Sphere ()
{
	return;
}