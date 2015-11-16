#include "Object.h"

Object::Object (Vector center, Color color, Material material)
{
	this->center = center;
	this->color = color;
	this->material = material;
}

Object::~Object ()
{
	return;
}
