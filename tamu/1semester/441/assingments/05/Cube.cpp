#include "Cube.h"

Cube::Cube (Vertex pos, double size)
{
	center = pos;
	this->size = size;
}

Cube::~Cube ()
{
	return;
}