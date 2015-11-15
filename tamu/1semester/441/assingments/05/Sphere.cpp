#include "Sphere.h"

Sphere::Sphere (Vector pos, double size)
{
	center = pos;
	this->size = size;
}

Sphere::~Sphere ()
{
	return;
}


Color Sphere::intersect (Vector u)
{	
	Color c;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	return c;
}