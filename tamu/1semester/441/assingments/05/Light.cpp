#include "Light.h"

Light::Light (Vector pos, Color color)
{
    center = pos;
    intensity = color;
}


Light::~Light ()
{
    return;
}


Color Light::getIntensity ()
{
	return intensity;
}