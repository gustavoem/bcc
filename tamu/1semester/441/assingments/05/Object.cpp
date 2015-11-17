#include "Object.h"

Object::Object (R3Vector center, Color color, Material material)
{
	this->center = center;
	this->color = color;
	this->material = material;
}

Object::~Object ()
{
	return;
}


bool Object::isLight ()
{
	return false;
}


R3Vector Object::getCenter ()
{
	return center;
}