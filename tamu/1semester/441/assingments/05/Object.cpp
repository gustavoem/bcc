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